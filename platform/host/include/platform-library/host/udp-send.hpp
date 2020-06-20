//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <cstdint>
#include <memory>

namespace host {

///
/// A simple class to send UDP messages to an IPv4 destination
///
class UDPSend
{
public:
    UDPSend();
    ~UDPSend();

    ///
    /// Returns ``true`` when the UDP socket is open
    ///
    bool is_open() const;

    ///
    /// Opens a UDP socket on the IPv4 address ``ipaddr`` and ``port``. Returns ``true`` if the UDP
    /// socket is opened successfully.
    ///
    /// .. note:: If the socket is already open, i.e. ``UDPSend::is_open() == true``, then the
    ///     socket is closed and a new socket is opened with the new ``ipaddr`` and ``port``.
    ///
    bool open(const char* ipaddr, uint16_t port);

    ///
    /// Sends the contents of the ``buffer`` of length ``len`` to the destination specified when
    /// opening ``UDPSend``.
    ///
    bool send(const uint8_t* buffer, std::size_t len);

    ///
    /// Closes the UDP socket.
    ///
    void close();

private:
    class Impl;
    std::unique_ptr<Impl> impl;
};
}  // namespace host