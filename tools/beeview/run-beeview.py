#!/usr/bin/env python3

# -----------------------------------------
# DESCRIPTION:
#   Opens a serial port and prints traces from the beetree application running on the nucleo board
# USAGE:
#   tracer <workspace-path> <port, e.g. /dev/tty.usbmodem1453>
# -----------------------------------------

import os
import sys
import serial
import struct
import json
import time
import traceback
from serial import Serial
from collections import namedtuple
from enum import Enum, auto

import pika
import subprocess
import signal
import argparse
import ctypes
import socket

# Named Types
RawPacket = namedtuple("RawPacket", "processor verbosity channel token args")

# Application context, i.e. persisted variables


class Context:
    def __init__(self):
        self.original_sigint = None
        self.trace_channel = None
        self.registry_channel = None
        self.webserver = None
        self.begin_ts = int(round(time.time() * 1000))

    def now(self):
        return int(round(time.time() * 1000)) - self.begin_ts

    def set_signal_callback(self, fnc):
        # set the signal callback
        self.original_sigint = signal.getsignal(signal.SIGINT)
        signal.signal(signal.SIGINT, fnc)

    def start_webserver(self, port):
        this_file = os.path.realpath(__file__)
        this_dir = os.path.dirname(this_file)
        self.webserver = subprocess.Popen(
            ["node", os.path.join(this_dir, "webserver.js"), str(port)])

    def make_connections(self):
        self.connection = pika.BlockingConnection(
            pika.ConnectionParameters('localhost'))

        self.trace_channel = self.connection.channel()
        self.trace_channel.queue_declare(queue='traces')

        self.registry_channel = self.connection.channel()
        self.registry_channel.queue_declare(queue='registry')

    def publish_trace(self, trace_msg):
        self.trace_channel.basic_publish(
            exchange='', routing_key='traces', body=json.dumps(trace_msg))

    def publish_registry(self, reg_msg):
        self.registry_channel.basic_publish(
            exchange='', routing_key='registry', body=json.dumps(reg_msg))

    def dispose(self):
        # restore the original signal handler as otherwise evil things will happen
        # in raw_input when CTRL+C is pressed, and our signal handler is not re-entrant
        signal.signal(signal.SIGINT, self.original_sigint)

        if self.trace_channel:
            print("Closing the trace channel")
            self.trace_channel.close()
            self.trace_channel = None

        if self.registry_channel:
            print("Closing the registry channel")
            self.registry_channel.close()
            self.registry_channel = None

        if self.webserver:
            print("Terminating webserver")
            self.webserver.terminate()
            self.webserver = None


app_context = Context()

# Methods


def read_serial(serial):
    START_CHAR = 0xA
    MAX_LEN = 4
    packet = None
    b = ord(serial.read())

    start_char = b >> 4
    trace_len = b & 0xf
    # print("Received byte: " + str(b))
    # print("Start Char: " + str(start_char))
    # print("Trace Len: " + str(trace_len))

    if(start_char == START_CHAR and trace_len <= MAX_LEN):  # 4 is the max number of ARGS
        # print('Start byte received with length ' + str(trace_len))
        # 3 bytes for the rest of the header
        # 4*trace_len bytes for the arguments
        # 4 bytes for the crc
        num_requested = 3 + 4*trace_len + 4
        rcv_bytes = serial.read(num_requested)
        if(len(rcv_bytes) == num_requested):
            channel = rcv_bytes[0] & 0x7
            verb = (rcv_bytes[0] >> 3) & 0x7
            proc = (rcv_bytes[0] >> 6) & 0x3
            token = struct.unpack("<H", rcv_bytes[1:3])[0]

            args = []
            for i in range(trace_len):
                idx = 3 + i*4
                unp = struct.unpack("<L", rcv_bytes[idx:(idx+4)])
                args.append(unp[0])

            crc = struct.unpack("<L", rcv_bytes[num_requested - 4:])[0]

            if(crc == 0):  # todo check crc against bytes when crc is implemented
                packet = RawPacket(proc, verb, channel, token, args)
            else:
                print("packet dropped - bad crc")
        else:
            print("packet dropped - did not receive all bytes")

    return packet


def exit_gracefully(signum, frame):
    app_context.dispose()
    sys.exit(0)

#
# bits
# msb                                 lsb
# eepp pppp pppp pppp 0ccc cccc cccc ccc0
#


def unpack_node_arg(x):
    tree = (x >> 30) & 0x03
    parent = (x >> 15) & 0x7FFF
    child = x & 0x7FFF

    return {"tree": tree, "parent": parent, "child": child}


def format_arg(mapping, arg):
    map = {
        'int': lambda x: ctypes.c_int32(x).value,
        'bool': lambda x: ctypes.c_bool(x).value,
        'boolean': lambda x: ctypes.c_bool(x).value
    }
    return map.get(mapping.lower(), lambda x: ctypes.c_uint32(x).value)(arg)

# The trace channels from beetree/trace/trace-defs.hpp


class TraceChannel(Enum):
    Log = 0       # Channel to send log messages on.
    Nodes = auto()         # Channel to send node changes on
    Registry = auto()       # Dedicated channel for continuous streaming registry banks
    # Channel dedicated to continuous streaming of key-value pairs.
    Diagnostics = auto()
    CH_4_Reserved = auto()  # Reserved for future use
    CH_5_Reserved = auto()  # Reserved for future use
    User_1 = auto()        # Dedicated channel for user
    User_2 = auto()          # Dedicated channel for user
    NUM_CHANNELS = auto()


def make_trace_msg(token_map, raw_packet):

    json_packet = None

    # look for token in the map based on the channel (number) and the token id (number)
    found_tokens = list(filter(
        lambda x: int(x["token_id"], 16) == raw_packet.token, token_map))
    if len(found_tokens) > 0 and raw_packet.channel < TraceChannel.NUM_CHANNELS.value:
        t = found_tokens[0]

        # get the message represented by the token
        if("msg" in t):
            msg = t["msg"]
        else:
            # default the trace message to the token's tag
            msg = t["name"]

        # format args
        map_args = []
        formatted_args = []
        args_start = 0
        if("args" in t):
            map_args = t["args"]

        if TraceChannel.Nodes.value == raw_packet.channel:
            # for nodes, unpack the first argument
            formatted_args.append(unpack_node_arg(raw_packet.args[0]))
            # inspect the other arguments starting at idx 1 now
            args_start = 1

        formatted_args.extend([format_arg(map_args[i], raw_packet.args[i]) if i < len(map_args)
                               else raw_packet.args[i]
                               for i in range(args_start, len(raw_packet.args))])

        json_packet = {
            "verb": raw_packet.verbosity,
            "proc": raw_packet.processor,
            "ch": raw_packet.channel,
            "ch_tag": TraceChannel(raw_packet.channel).name,
            "msg": msg,
            "args": formatted_args,
            "ts": app_context.now()
        }

    return json_packet


def format_reg_value(unit_type, val):

    map = {
        'deg': lambda x: ctypes.c_int32(x).value,
        'mm': lambda x: ctypes.c_int32(x).value,
        'mm/s': lambda x: ctypes.c_int32(x).value,
        'mm/s^2': lambda x: ctypes.c_int32(x).value,
        'mrad': lambda x: ctypes.c_int32(x).value,
        'mrad/s': lambda x: ctypes.c_int32(x).value,
        'ticks': lambda x: ctypes.c_int32(x).value,
        'bool': lambda x: ctypes.c_bool(x).value,
        'boolean': lambda x: ctypes.c_bool(x).value,
        'flags': lambda x: '{:#08X}'.format(x)
    }
    return map.get(unit_type.lower(), lambda x: ctypes.c_uint32(x).value)(val)


def make_registry_msg(trace_msg, registry_map):
    reg_msg = None
    if len(trace_msg["args"]) >= 3:
        bank_idx = trace_msg["args"][0]
        item_idx = trace_msg["args"][1]
        item_value = trace_msg["args"][2]

        if bank_idx < len(registry_map):
            bank = registry_map[bank_idx]
            items = bank["items"]

            if items and item_idx < len(items):
                item = items[item_idx]

                reg_msg = {
                    "bank": bank["name"],
                    "bank_id": bank_idx,
                    "item": item["desc"],
                    "item_id": item_idx,
                    "item_value": format_reg_value(item["type"], item_value),
                    "item_type": item["type"]
                }
    return reg_msg


class SerialReader:
    '''
    Class SerialReader

    A simple serial port reader.

    Synopsis
    --------
    ::
        # Create a Serial Port Reader with
        #   device: dev/tty.usbmodem1453
        #   baud rate: 460800
        rcv = SerialReader('dev/tty.usbmodem1453', 460800)

        # open it
        rcv.open()

        # read 12 bytes
        b = rcv.read(bytesToRead=12)

        # close the receiver
        rcv.close()
    '''

    def __init__(self, device, baud):
        self.ser = Serial()
        self.ser.port = device
        self.ser.baudrate = baud
        self.ser.bytesize = serial.EIGHTBITS
        self.ser.stopbits = serial.STOPBITS_ONE
        self.ser.parity = serial.PARITY_NONE

    def open(self):
        self.ser.open()

    def read(self, bytesToRead=1):
        return self.ser.read(bytesToRead)

import queue

class UDPReader:
    '''
    Class UDPReader

    A simple udp network message reader.

    Synopsis
    --------
    ::
        # Create a UDP Message Reader on port 1225
        rdr = UDPReader(port=1225)

        # open it
        rdr.open()

        # read 12 bytes
        b = rdr.read(bytesToRead=12)

        # close the receiver
        rdr.close()
    '''

    def __init__(self, port=1225):
        self.local_host = "127.0.0.1"
        self.port = port
        self.buffer = bytearray("",'utf-8')
        self.sock = socket.socket(socket.AF_INET,  # Internet
                                  socket.SOCK_DGRAM)  # UDP

    def open(self):
        self.sock.bind((self.local_host, self.port))

    def read(self, bytesToRead=1):
        
        # refill the buffer
        start = time.monotonic()
        while bytesToRead > len(self.buffer) and (time.monotonic() - start) < 1000.0:
            b = self.sock.recvfrom(512,0)[0]
            self.buffer.extend(b)

        msg = self.buffer[:bytesToRead]
        self.buffer = self.buffer[bytesToRead:]

        return msg


def main(args):

    # the real workspace is in the 'share' directory which contains the token maps and registries.
    workspaces = [os.path.join(args.workspace, 'share', 'beetree')]

    # is the workspace valid?
    if not os.path.exists(workspaces[0]):
        raise Exception("invalid workspace: " + args.workspace)

    # its possible that the application does not have a token or registry files.
    appWorkspace = os.path.join(args.workspace, 'share', args.application)
    if os.path.exists(appWorkspace):
        workspaces.append(appWorkspace)


    token_map = []
    registry_map = []
    registry_idx = []

    for workspace in workspaces:
        for file in [os.path.abspath(os.path.join(workspace, f)) for f in os.listdir(workspace) if f.endswith(".json")]:
            with open(file, 'r') as ofile:
                j = json.load(ofile)
                if "tokens" in j:
                    # load the tokens file and add to the map
                    print("Found token map: {}".format(file))
                    token_map.extend(j["tokens"])
                elif "name" in j and "items" in j:
                    # load the registry file and add the register to the map
                    print("Found registry: {}".format(file))
                    registry_map.append(
                        {"name": j["name"], "items": j["items"], "idx": 0})
                elif "index" in j:
                    print("Found index: {}".format(file))
                    registry_idx = j["index"]
                else:
                    print("File contents are unknown. Skipping {}".format(file))

    # associate the registry index to the registry item
    # the registry index is created by the build and not by the developer
    # it is used to associate the developers individual register banks with
    # the generated enumeration used when enumerating the registry banks.
    for reg in registry_map:
        for (idx, name) in enumerate(registry_idx):
            if reg["name"] == name:
                reg["idx"] = idx
                break

    # sort the list for quick access when a message is received
    token_map.sort(key=lambda t: int(t["token_id"], 16))
    registry_map.sort(key=lambda reg: reg["idx"])

    print("Start webserver on Port " + str(args.port))
    app_context.start_webserver(args.port)
    print("Establishing Connections...")
    app_context.make_connections()

    ser = None
    if args.internal_net:
        print("Opening UDP connection for HelloWorld")
        ser = UDPReader()
    else:
        print("Opening serial port on " + args.serial_device +
              " with baud rate " + str(args.baud))
        ser = SerialReader(args.serial_device, args.baud)
    ser.open()

    while(True):
        raw_packet = read_serial(ser)
        if not raw_packet:
            continue

        # look for token in the map based on the channel (number) and the token id (number)
        trace_msg = make_trace_msg(token_map, raw_packet)
        if not trace_msg:
            continue

        # publish every channel except registry to the traces
        if(trace_msg["ch"] != TraceChannel.Registry.value):
            app_context.publish_trace(trace_msg)
        else:  # process the message more
            reg_msg = make_registry_msg(trace_msg, registry_map)
            if reg_msg:
                app_context.publish_registry(reg_msg)


if __name__ == "__main__":
    # parse arguments
    parser = argparse.ArgumentParser(
        description="BeeTree's diagnostic webtool")

    defaultWorkspace = os.path.join(
        os.path.dirname(os.path.realpath(__file__)), "..")

    parser.add_argument("application", help="the name of the application interfacing with BeeView, e.g. helloworld, simplebee")
    parser.add_argument("-w", "--workspace",
                        help="the workspace directory defaulting to " + defaultWorkspace,
                        default=defaultWorkspace)
    webServerGroup = parser.add_argument_group("Web Server Parameters")
    webServerGroup.add_argument("-p", "--port", type=int,
                                help="the web server's port, defaulting to 4200",
                                default=4200)
    serialDeviceGroup = parser.add_argument_group(
        "BeeTree's Embedded Serial Communication Params")
    serialDeviceGroup.add_argument("-s", "--serial_device",
                                   help="beetree's serial device interface, e.g. /dev/tty.usbmodem1443")
    serialDeviceGroup.add_argument("-b", "--baud", type=int,
                                   help="the serial port's baud rate to the device. defaulting to 460800",
                                   default=460800)

    udpGroup = parser.add_argument_group("BeeTree's Internal Network for Helloworld")
    udpGroup.add_argument("--internal_net",
                          help="select to use BeeView with BeeTree's hello world",
                          action="store_true")
    args = parser.parse_args()

    try:
        app_context.set_signal_callback(exit_gracefully)
        main(args)
    except:  # catch *all* exceptions        
        traceback.print_exc()
        exit_gracefully(None, None)
