//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include <array>
#include <future>
#include <nlohmann/json.hpp>

#include "internal-platform.hpp"

namespace helloworld {

struct BootException
{};

// for convenience
using json = nlohmann::json;

void trace(const std::string& type, const std::string& name, bool value)
{
    std::cout << type << ": " << name << " " << (value ? "ON" : "OFF") << std::endl;
}

void InternalPlatform::DiscreteOutput::set()
{
    this->value = true;
    trace("DO", this->name, this->value);
}
void InternalPlatform::DiscreteOutput::clear()
{
    this->value = false;
    trace("DO", this->name, this->value);
}
void InternalPlatform::DiscreteOutput::toggle()
{
    this->value = !this->value;
    trace("DO", this->name, this->value);
}
bool InternalPlatform::DiscreteOutput::is_set() const { return this->value; }

bool InternalPlatform::SerialDevice::open(const char* host, uint16_t port)
{
    return udp.open(host, port);
}

int32_t InternalPlatform::SerialDevice::write(std::size_t              address,
                                              const uint8_t*           data,
                                              std::size_t              len,
                                              bte::chrono::duration_ms timeout)
{
    if (udp.send(data, len))
    {
        return len;
    }
    return 0;
}
int32_t InternalPlatform::SerialDevice::read(std::size_t              address,
                                             uint8_t*                 data,
                                             std::size_t              len,
                                             bte::chrono::duration_ms timeout)
{
    return 0;
}

void InternalPlatform::SerialDevice::close() { udp.close(); }

InternalPlatform& InternalPlatform::instance()
{
    static InternalPlatform s_instance;
    return s_instance;
}

bool InternalPlatform::boot()
{
    teardown();

    try
    {
        if (!vcp.open(local_host(), TX_PORT))
        {
            throw BootException{};
        }

        if (!m_udpRX.open(RX_PORT))
        {
            throw BootException{};
        }

        {
            std::promise<void> promise;

            auto future = promise.get_future();

            m_thread = std::thread(
                [this](std::promise<void> p) {
                    this->m_is_running = true;
                    p.set_value();
                    this->run_coms();
                },
                std::move(promise));

            if (std::future_status::ready != future.wait_for(std::chrono::seconds{1}))
            {
                throw BootException{};
            }
        }
    }
    catch (BootException)
    {
        teardown();
        return false;
    }

    return true;
}

void InternalPlatform::run_coms()
{
    constexpr std::chrono::microseconds TIMEOUT = std::chrono::milliseconds{10};
    std::array<uint8_t, 512>            buffer;

    while (m_is_running)
    {
        auto nbytes = m_udpRX.recv(buffer.begin(), buffer.size(), TIMEOUT);
        if (nbytes > 0)
        {
            auto msg = json::parse(buffer.begin(), buffer.begin() + nbytes);
            for (const auto& it : msg.items())
            {
                const auto& key   = it.key();
                const auto& value = it.value();
                if (key == "user_btn_depressed")
                {
                    this->user_btn.set(value.get<bool>());
                }
            }
        }
    }
}

void InternalPlatform::teardown()
{
    m_is_running = false;
    if (m_thread.joinable())
    {
        m_thread.join();
    }

    m_udpRX.close();
    vcp.close();
}

bool boot(Platform&) { return InternalPlatform::instance().boot(); }
void teardown(Platform&) { InternalPlatform::instance().teardown(); }

// > Clock
bte::ISystemClock& Platform::clock() { return InternalPlatform::instance().clock; }

// > Discrete Outputs
bte::IDiscreteOutput& Platform::led() { return InternalPlatform::instance().led; }
bte::IDiscreteOutput& Platform::debug() { return InternalPlatform::instance().debug; }

// > Discrete Inputs
bte::IDiscreteInput& Platform::user_btn() { return InternalPlatform::instance().user_btn; }

bte::ISerialDevice& Platform::vcp() { return InternalPlatform::instance().vcp; }
}  // namespace helloworld