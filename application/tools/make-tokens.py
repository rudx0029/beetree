#!/usr/bin/env python3
'''
***********
Make Tokens
***********

Generates a cpp header file and JSON tokens map given a list of JSON tokens files.

:: seealso: BeeTree design documentation for JSON token file formats and usage

Synopsis
--------

::
    python make-tokens.py path/to/generated/header.hpp path/to/generated/map.json paths/to/tokens.json ...

Requires
--------

``crcmod``

'''

import json
import sys
import glob
import os
import argparse
import crcmod.predefined


from operator import attrgetter, itemgetter
from collections import namedtuple, defaultdict
Token = namedtuple('Token', 'channel tag token')


def log(msg):
    print("make-tokens: " + msg)


def flatten_token(namespace, token_id, token):
    '''
    Adds 'namespace' and 'token_id' to the token read from the file.

    Parameters
    ----------

    ``namespace``
        C/C++ namespace the token belongs to.
    ``token_id``
        Generated token ID or 0 if not yet generated
    ``token``
        Original token from the JSON tokens file

    Returns
    -------
        ``token`` with ``namespace`` and ``token_id`` fields added.
    '''
    flat_token = {
        'namespace': namespace,
        'token_id': token_id,
        'name': token['name'],
        'msg': '',
        'args': '',
    }

    if 'msg' in token:
        flat_token['msg'] = token['msg']
    if 'args' in token:
        flat_token['args'] = token['args']

    return flat_token


def collect_tokens(namespace, tokens):
    '''
    Given a list of tokens with subgroups of tokens, organizes the tokens into
    a flat list and adds the ``namespace`` field and a ``token_id`` placeholder
    to each token.

    Parameters
    ----------

    ``namespace``
        C/C++ namespace the token belongs to.
    ``tokens``
        Original tokens from the JSON tokens file including any subgroups

    Returns
    -------

    A flat list of tokens
    '''
    collected_tokens = [
        flatten_token(namespace, 0, t) for t in tokens if "name" in t]

    groups = [g for g in tokens if "group" in g and "tokens" in g]
    for g in groups:
        collected_tokens.extend(collect_tokens(namespace, g["tokens"]))

    return collected_tokens


def collect_tokens_from(path):
    '''
    For the given path, opens the JSON file contain tokens and subgroups of tokens. The
    tokens are extracted and flat list of tokens is generated and returned.

    Parameters
    ----------

    ``path``
        The path to the JSON file containing the tokens.

    Returns
    -------

    A flat list of tokens read from a tokens JSON file.
    '''
    j = None
    tokens = []
    try:
        with open(path, 'r') as infile:
            j = json.load(infile)

        if not j:
            raise Exception(
                "Token manifest is invalid or not in the right format for " + path)
        if not "namespace" in j:
            raise Exception(
                "Tokens manifest is missing 'namespace' field.")
        if not "tokens" in j:
            raise Exception("Tokens manifest is missing 'tokens' field")
        tokens.extend(collect_tokens(j['namespace'], j["tokens"]))
    except Exception as e:
        log("Exception Caught" + str(e))
    
    return tokens


def token_2_constexpr(t):
    s = 'constexpr bte::TraceToken '
    s += t['name']
    s += "    { /*token id*/ " + str(t['token_id']) + "};"
    return s


crc16_func = crcmod.predefined.mkCrcFun('crc-16-dnp')
def generate_token_id(namespace, tokenName):
    return hex(crc16_func(str(namespace + tokenName).encode('utf-8')))

def main():
    description = "Generates trace token header file and respective json map"
    parser = argparse.ArgumentParser(description=description)

    parser.add_argument(
        'header', help="the path to the output tokens header file, e.g. path/to/trace-tokens.hpp")
    parser.add_argument('map',
                        help="the path to the output tokens map file, e.g. path/to/trace-tokens-map.json")

    parser.add_argument('paths', nargs='+',
                        help="the path to the tokens json file, e.g. path/to/tokens.json")

    args = parser.parse_args()

    tokens = []
    indexed_tokens = defaultdict(list)

    for path in args.paths:
        t = collect_tokens_from(path)
        log("read " + str(len(t)) + " tokens from " + path + ".")
        tokens.extend(t)
    

    log("indexing tokens")
    for t in tokens:
        indexed_tokens[t['namespace']].append(t)

    log("generating header")
    header = []
    header.append("#pragma once")
    header.append("")
    header.append("#include \"beetree/trace/trace-defs.hpp\"")
    header.append("")
    header.append("/*")
    header.append(" * This file is auto generated. Please do not modify!")
    header.append(" */")

    for (namespace, tokens) in indexed_tokens.items():
        header.append("")
        header.append("namespace " + namespace + "{")
        header.append("namespace tokens {")

        for t in tokens:
            t["token_id"] = generate_token_id(namespace,t['name'])
            header.append("    " + token_2_constexpr(t))

        header.append("} // tokens namespace")
        header.append("} // " + namespace + " namespace")


    for f in [args.header, args.map]:
        try:
            os.remove(os.path.realpath(f))
        except:
            pass
    dir_path = os.path.dirname(os.path.abspath(args.header))
    os.makedirs(dir_path, exist_ok=True)
    with open(args.header, 'x') as outfile:
        for h in header:
            outfile.write(h)
            outfile.write('\n')
        log("tokens written to " + outfile.name)

    dir_path = os.path.dirname(os.path.abspath(args.map))
    os.makedirs(dir_path, exist_ok=True)
    with open(args.map, 'x') as outfile:
        json.dump({"tokens": tokens}, outfile, indent=4, sort_keys=True)
        log("token map written to " + outfile.name)

    log("Goodbye!")


if __name__ == "__main__":
    main()
