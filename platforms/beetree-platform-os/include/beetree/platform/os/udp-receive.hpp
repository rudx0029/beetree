//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE.txt', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <chrono>
#include <memory>

namespace host {

///
class UDPReceive
{
public:
    UDPReceive();
    ~UDPReceive();

    ///
    /// Returns ``true`` if the UDP socket is bound to a port and ready to receive messages
    ///
    bool is_open() const;

    ///
    /// Binds the UDP socket to a local ``port``, making it ready to receive messages.
    ///
    bool open(uint16_t port);

    ///
    /// Blocks until a UDP message is received or until the operation exceeds the ``timeout``
    /// duration. When a UDP message is received and 0 or more bytes are copied to the ``buffer``,
    /// the method returns number of bytes copied to the buffer. If the method returns a negative
    /// number, the operation failed.
    ///
    int recv(uint8_t* buffer, std::size_t len, std::chrono::microseconds timeout);

    ///
    /// Closes the udp socket.
    ///
    void close();

private:
    class Impl;
    std::unique_ptr<Impl> impl;
};
}  // namespace host