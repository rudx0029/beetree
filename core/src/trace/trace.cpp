//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/trace/trace.hpp"

namespace bte {

static TraceManager* s_manager = nullptr;

void set_trace_manager(TraceManager* manager) { s_manager = manager; }
}  // namespace bte

namespace trace {
using TraceStream    = bte::TraceStream;
using TraceToken     = bte::TraceToken;
using TraceChannel   = bte::TraceChannel;
using TraceVerbosity = bte::TraceVerbosity;

TraceStream channels::registry(const TraceToken& token)
{
    return TraceStream(bte::s_manager, token, TraceChannel::Registry, TraceVerbosity::Debug);
}
TraceStream channels::diag(const TraceToken& token)
{
    return TraceStream(bte::s_manager, token, TraceChannel::Diagnostics, TraceVerbosity::Debug);
}
TraceStream channels::nodes(const TraceToken& token)
{
    return TraceStream(bte::s_manager, token, TraceChannel::Nodes, TraceVerbosity::Debug);
}
TraceStream channels::user1(const TraceToken& token)
{
    return TraceStream(bte::s_manager, token, TraceChannel::User_1, TraceVerbosity::Debug);
}

TraceStream channels::user2(const bte::TraceToken& token)
{
    return TraceStream(bte::s_manager, token, TraceChannel::User_2, TraceVerbosity::Debug);
}

bte::TraceStream channels::log(const bte::TraceToken& token, const bte::TraceVerbosity& verb)
{
    return TraceStream(bte::s_manager, token, TraceChannel::Log, verb);
}

TraceStream debug(const TraceToken& token) { return channels::log(token, TraceVerbosity::Debug); }

TraceStream info(const TraceToken& token) { return channels::log(token, TraceVerbosity::Info); }

TraceStream warn(const TraceToken& token) { return channels::log(token, TraceVerbosity::Warn); }

TraceStream error(const TraceToken& token) { return channels::log(token, TraceVerbosity::Error); }

TraceStream fatal(const TraceToken& token) { return channels::log(token, TraceVerbosity::Fatal); }
}  // namespace trace