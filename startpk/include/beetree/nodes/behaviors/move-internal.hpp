//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/engine/recipe.hpp"
#include "beetree/units/motion-profile.hpp"

namespace bte {

// > interface
Recipe make_move(delegate::Loop loop, delegate::TraceEvt trace_evt);
Result loop_move(Context& ctx, const units::MotionProfile& data_mp);
void   on_trace_move(TraceStream& s, Context& ctx, const units::MotionProfile& data_mp);

// > tree to run time conversion

template <const units::MotionProfile& MOTION>
Result loop_move(Context& ctx)
{
    return loop_move(ctx, MOTION);
}

template <const units::MotionProfile& MOTION>
void on_trace_move(TraceStream& s, Context& ctx)
{
    on_trace_move(s, ctx, MOTION);
}

template <const units::MotionProfile& MOTION>
Recipe make_move()
{
    return make_move(loop_move<MOTION>, on_trace_move<MOTION>);
}
}  // namespace bte