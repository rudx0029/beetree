//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "platform-library/host/udp-send.hpp"

#include <cstdio>
#include <cstring>

#ifdef __cplusplus
extern "C"
{
#include <arpa/inet.h>   // For inet_addr()
#include <netinet/in.h>  // For sockaddr_in
#include <sys/socket.h>  // For socket(), connect(), send(), and recv()
#include <sys/types.h>   // For data types
#include <unistd.h>      // For close()
}
#endif

namespace host {

struct OpenException
{};

struct SendException
{};

///
/// PImpl Class for UDP Send
///
class UDPSend::Impl
{
public:
    static constexpr int INVALID_SOCKET{-1};
    int                  socket{INVALID_SOCKET};
    struct sockaddr_in   serverAddr;

    bool is_open() const { return this->socket > INVALID_SOCKET; }

    bool open(const char* ipaddr, uint16_t port)
    {
        if (is_open())
        {
            close();
        }

        // create a socket
        try
        {
            // check ipaddres
            if (!ipaddr)
            {
                throw OpenException{};
            }

            // create the socket
            socket = ::socket(AF_INET, SOCK_DGRAM, 0);
            if (socket < 0)
            {
                throw OpenException{};
            }

            // configure settings
            serverAddr.sin_family      = AF_INET;
            serverAddr.sin_port        = htons(port);
            serverAddr.sin_addr.s_addr = inet_addr(ipaddr);
            memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
        }
        catch (OpenException)
        {
            this->close();
        }

        return is_open();
    }

    bool send(const uint8_t* msg, std::size_t len)
    {
        return ::sendto(socket,
                        msg,
                        len,
                        /*flags*/ 0,
                        reinterpret_cast<struct sockaddr*>(&serverAddr),
                        sizeof(serverAddr)) >= 0;
    }

    void close()
    {
        if (is_open())
        {
            // close the socket descriptor
            ::close(socket);
        }
        socket = INVALID_SOCKET;
    }
};

//-------------------------------
// UDPSend Implementation
//-------------------------------
UDPSend::UDPSend() : impl(new Impl()) {}
UDPSend::~UDPSend() { impl->close(); }
bool UDPSend::open(const char* ipaddr, uint16_t port) { return impl->open(ipaddr, port); }
bool UDPSend::send(const uint8_t* msg, std::size_t len) { return impl->send(msg, len); }
bool UDPSend::is_open() const { return impl->is_open(); }
void UDPSend::close() { impl->close(); }

}  // namespace host