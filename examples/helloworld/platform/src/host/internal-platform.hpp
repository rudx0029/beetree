//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <atomic>
#include <iostream>
#include <string>
#include <thread>
#include "helloworld-platform/helloworld-platform.hpp"
#include "platform-library/host/system-clock.hpp"
#include "platform-library/host/udp-receive.hpp"
#include "platform-library/host/udp-send.hpp"

namespace helloworld {
class InternalPlatform
{
public:
    using SystemClock = host::SystemClock;
    class DiscreteOutput : public bte::IDiscreteOutput
    {
    public:
        DiscreteOutput(const std::string& n) : name(n) {}
        void set() override;
        void clear() override;
        void toggle() override;
        bool is_set() const override;

    private:
        std::string name;
        bool        value = false;
    };

    class DiscreteInput : public bte::IDiscreteInput
    {
    public:
        void set(bool value) { m_value = value; }
        bool is_set() const override { return m_value; }

    private:
        std::atomic_bool m_value{false};
    };

    /// The internal platform's Serial Device sends serial writes
    /// as UDP messages to the endpoint ipv4 127.0.0.1, port 1225
    class SerialDevice : public bte::ISerialDevice
    {
    public:
        bool    open(const char* host, uint16_t port);
        void    close();
        int32_t write(std::size_t              address,
                      const uint8_t*           data,
                      std::size_t              len,
                      bte::chrono::duration_ms timeout) override;
        int32_t read(std::size_t              address,
                     uint8_t*                 data,
                     std::size_t              len,
                     bte::chrono::duration_ms timeout) override;

    private:
        host::UDPSend udp;
    };

    static InternalPlatform& instance();
    bool                     boot();
    void                     teardown();

    // > MEMBERS

    SystemClock    clock;
    DiscreteOutput led{"led"};
    DiscreteOutput debug{"debug"};
    DiscreteInput  user_btn;
    SerialDevice   vcp;

    static constexpr const char* local_host() { return "127.0.0.1"; }
    static constexpr uint16_t    TX_PORT{1225};  // like christmas
    static constexpr uint16_t    RX_PORT{TX_PORT + 1};

private:
    InternalPlatform() = default;

    void run_coms();

    std::thread      m_thread;
    host::UDPReceive m_udpRX;
    std::atomic_bool m_is_running{false};
};
}  // namespace helloworld