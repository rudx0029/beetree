//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/trace/trace-defs.hpp"
#include "beetree/trace/trace-manager.hpp"
#include "beetree/trace/trace-stream.hpp"

namespace bte {
void set_trace_manager(TraceManager* manager);
}  // namespace bte

namespace trace {
// Log Channel Writers
bte::TraceStream debug(const bte::TraceToken& token);
bte::TraceStream info(const bte::TraceToken& token);
bte::TraceStream warn(const bte::TraceToken& token);
bte::TraceStream error(const bte::TraceToken& token);
bte::TraceStream fatal(const bte::TraceToken& token);

// Channel Specific Writers
struct channels
{
    static bte::TraceStream log(const bte::TraceToken& token, const bte::TraceVerbosity& verb);
    static bte::TraceStream registry(const bte::TraceToken& token);
    static bte::TraceStream diag(const bte::TraceToken& token);
    static bte::TraceStream nodes(const bte::TraceToken& token);
    static bte::TraceStream user1(const bte::TraceToken& token);
    static bte::TraceStream user2(const bte::TraceToken& token);
};
}  // namespace trace