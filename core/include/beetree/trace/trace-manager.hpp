//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/btos/flag-types.hpp"
#include "beetree/trace/trace-defs.hpp"

namespace bte {
class TraceManager final
{
public:
    TraceManager();

    void set_listener(TraceListener* listener);
    void set_processor(TraceProcessor process);
    void set_verbosity(TraceVerbosity verbosity);

    void log(const TracePackage& package);

    void enable_channel(TraceChannel channel);
    void disable_channel(TraceChannel channel);

private:
    TraceListener*           m_listener  = nullptr;
    TraceProcessor           m_processor = TraceProcessor::ID_0;
    TraceVerbosity           m_verbosity = TraceVerbosity::Info;
    bte::Flags<TraceChannel> m_channels;
};
}  // namespace bte