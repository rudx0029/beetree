///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file Trace TraceStream implementation
///-----------------------------------------------------------------------------

#include "beetree/trace/trace-stream.hpp"

namespace bte {
TraceStream::TraceStream(TraceManager*     manager,
                         const TraceToken& token,
                         TraceChannel      channel,
                         TraceVerbosity    verbosity)
    : m_manager(manager)
{
    m_package.token     = token;
    m_package.channel   = channel;
    m_package.verbosity = verbosity;
}

TraceStream::TraceStream(TraceStream&& mv)
    : m_package(std::move(mv.m_package)), m_manager(std::move(mv.m_manager))
{
    mv.m_manager = nullptr;
}

TraceStream::~TraceStream()
{
    if (m_manager != nullptr)
    {
        m_manager->log(m_package);
    }
}

void TraceStream::add_argument(uint32_t arg)
{
    // todo: check for endianess
    if (m_package.num_args < trace_prot::MAX_TOKEN_ARGS)
    {
        m_package.args[m_package.num_args] = arg;
        m_package.num_args++;
    }
}

TraceStream& TraceStream::operator<<(uint64_t arg)
{
    add_argument(static_cast<uint32_t>(arg));
    return *this;
}

TraceStream& TraceStream::operator<<(int64_t arg)
{
    add_argument(static_cast<int32_t>(arg));
    return *this;
}

TraceStream& TraceStream::operator<<(uint32_t arg)
{
    add_argument(arg);
    return *this;
}
TraceStream& TraceStream::operator<<(int32_t arg)
{
    uint32_t* pArg = reinterpret_cast<uint32_t*>(&arg);
    add_argument(*pArg);
    return *this;
}
TraceStream& TraceStream::operator<<(uint16_t arg)
{
    add_argument(arg);
    return *this;
}
TraceStream& TraceStream::operator<<(int16_t arg)
{
    uint16_t* pArg = reinterpret_cast<uint16_t*>(&arg);
    add_argument(*pArg);
    return *this;
}
TraceStream& TraceStream::operator<<(uint8_t arg)
{
    add_argument(arg);
    return *this;
}
TraceStream& TraceStream::operator<<(int8_t arg)
{
    uint8_t* pArg = reinterpret_cast<uint8_t*>(&arg);
    add_argument(*pArg);
    return *this;
}

TraceStream& TraceStream::operator<<(float arg)
{
    uint32_t* pArg = reinterpret_cast<uint32_t*>(&arg);
    add_argument(*pArg);
    return *this;
}
TraceStream& TraceStream::operator<<(double arg)
{
    float     f    = static_cast<float>(arg);
    uint32_t* pArg = reinterpret_cast<uint32_t*>(&f);
    add_argument(*pArg);
    return *this;
}
TraceStream& TraceStream::operator<<(bte::Clock::milliseconds arg)
{
    return this->operator<<(static_cast<int32_t>(arg.count()));
}

TraceStream& TraceStream::operator<<(bool arg)
{
    return this->operator<<(static_cast<uint32_t>(arg ? 1 : 0));
}

TraceStream& TraceStream::operator<<(const TraceToken& token)
{
    uint32_t     t = (token.id << 16) | static_cast<uint16_t>(m_package.channel);
    return this->operator<<(t);
}

TraceStream& TraceStream::operator<<(const char* string)
{
    std::size_t it    = 0;
    std::size_t pos   = sizeof(uint32_t) - 1;
    uint32_t    dword = 0;

    while (0 != string[it] && m_package.num_args < trace_prot::MAX_TOKEN_ARGS)
    {
        dword |= string[it] << 8 * pos;

        if (pos == 0)
        {
            add_argument(dword);
            dword = 0;
            pos   = sizeof(uint32_t) - 1;
        }

        it++;
        pos--;
    }

    return *this;
}
}  // namespace bte