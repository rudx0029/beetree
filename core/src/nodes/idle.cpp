//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/nodes/idle.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"

namespace bte {
namespace {
struct Data
{
    Clock::ms duration;
    Clock::tp start_tp;
};
}  // namespace

void setup_idle(Context& ctx, const Clock::ms& duration)
{
    Data* d     = ctx.get_data<Data>();
    d->duration = duration;
    d->start_tp = Clock::now();
}

static Result loop(Context& ctx)
{
    Status status = Status::Running;
    Data*  d      = ctx.get_data<Data>();

    if (Clock::elapsed(d->start_tp) > d->duration)
    {
        status = Status::Success;
    }

    return {status};
}

static void on_trace(TraceStream& s, Context& ctx) { s << ctx.get_data<Data>()->duration; }

Recipe make_idle(delegate::Setup s)
{
    return Builder(tokens::IdleNode, loop)
        .add_data<Data>()
        .add_setup(s)
        .add_handler(on_trace)
        .finalize();
}

}  // namespace bte