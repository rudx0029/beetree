//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/trace/trace-manager.hpp"
#include "beetree/btos/flags.hpp"

namespace bte {

TraceManager::TraceManager()
    : m_channels(std::numeric_limits<uint32_t>::max())  // turn on all channel
{
#ifdef DEBUG
    m_verbosity = Verbosity::Debug;
#endif
}
void TraceManager::set_listener(TraceListener* listener) { m_listener = listener; }

void TraceManager::set_processor(TraceProcessor p) { m_processor = p; }

void TraceManager::set_verbosity(TraceVerbosity v) { m_verbosity = v; }

void TraceManager::enable_channel(TraceChannel channel) { flags::set(m_channels, channel); }

void TraceManager::disable_channel(TraceChannel channel) { flags::reset(m_channels, channel); }

void TraceManager::log(const TracePackage& package)
{
    if (m_listener != nullptr && package.verbosity >= m_verbosity &&
        flags::test(m_channels, package.channel))
    {
        m_listener->on_log_received(m_processor, package);
    }
}
}  // namespace bte