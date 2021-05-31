//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/platform/os/udp-receive.hpp"

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

struct RecvException
{
    struct Timeout
    {};
};

///
/// PImpl Class for UDP Send
///
class UDPReceive::Impl
{
public:
    static constexpr int INVALID_SOCKET{-1};
    int                  socket{INVALID_SOCKET};

    bool is_open() const { return this->socket > INVALID_SOCKET; }

    bool open(uint16_t port)
    {
        if (is_open())
        {
            close();
        }

        // create a socket
        try
        {
            // create the socket
            socket = ::socket(AF_INET, SOCK_DGRAM, 0);
            if (socket < 0)
            {
                throw OpenException{};
            }

            // configure settings
            struct sockaddr_in serverAddr;
            memset(&serverAddr, 0, sizeof(serverAddr));
            serverAddr.sin_family      = AF_INET;
            serverAddr.sin_port        = htons(port);
            serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

            // bind the socket to the port
            if (bind(socket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) <
                0)
            {
                throw OpenException{};
            }
        }
        catch (OpenException)
        {
            this->close();
        }

        return is_open();
    }

    int recv(uint8_t* buff, std::size_t len, std::chrono::microseconds timeout)
    {
        int nReceived = 0;
        try
        {
            if (!is_open())
            {
                throw RecvException{};
            }

            fd_set rfds;
            FD_ZERO(&rfds);
            FD_SET(socket, &rfds);

            const auto sec = std::chrono::duration_cast<std::chrono::seconds>(timeout);

            struct timeval tv;
            tv.tv_sec = sec.count();
            tv.tv_usec =
                std::chrono::duration_cast<std::chrono::microseconds>(timeout - sec).count();

            int retval = ::select(socket + 1, &rfds, nullptr, nullptr, &tv);
            if (0 == retval) throw RecvException::Timeout{};
            if (retval < 0) throw RecvException{};

            struct sockaddr_in remoteAddr;
            socklen_t          addrlen = sizeof(remoteAddr);

            nReceived = ::recvfrom(
                socket, buff, len, 0, reinterpret_cast<struct sockaddr*>(&remoteAddr), &addrlen);
            if (nReceived < 0) throw RecvException{};
        }
        catch (RecvException)
        {
            nReceived = -1;
        }
        catch (RecvException::Timeout)
        {
            nReceived = 0;
        }

        return nReceived;
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
};  // namespace host

//-------------------------------
// UDPReceive Implementation
//-------------------------------
UDPReceive::UDPReceive() : impl(new Impl()) {}
UDPReceive::~UDPReceive() { impl->close(); }
bool UDPReceive::open(uint16_t port) { return impl->open(port); }
int  UDPReceive::recv(uint8_t* buffer, std::size_t len, std::chrono::microseconds timeout)
{
    return impl->recv(buffer, len, timeout);
}
bool UDPReceive::is_open() const { return impl->is_open(); }
void UDPReceive::close() { impl->close(); }

}  // namespace host