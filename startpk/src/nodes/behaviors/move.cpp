//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/nodes/behaviors/move.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/nodes/blackboard.hpp"
#include "beetree/services/i-motion-service.hpp"
#include "beetree/startpk/tokens.hpp"
#include "beetree/units/units.hpp"

namespace bte {
namespace {
using units::as;
using units::mmps;
using units::mmpss;
using units::MotionProfile;
using units::mradps;
}  // namespace

Result loop_move(Context& ctx, const MotionProfile& mp)
{
    auto status = Status::Fail;
    auto svc    = blackboard::update<IMotionService>();
    if (svc)
    {
        svc->move(mp);
        status = Status::Success;
    }

    return {status};
}

void on_trace_move(TraceStream& s, Context& ctx, const MotionProfile& mp)
{
    s << as<mmps>(mp.velocity) << as<mmpss>(mp.acceleration) << as<mradps>(mp.angularVelocity);
}

Recipe make_move(delegate::Loop loop_w_params, delegate::TraceEvt trace_evt)
{
    return Builder(tokens::SetMotionProfileNode, loop_w_params).add_handler(trace_evt).finalize();
}
}  // namespace bte