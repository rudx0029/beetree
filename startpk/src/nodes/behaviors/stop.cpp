//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/nodes/behaviors/stop.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/nodes/blackboard.hpp"
#include "beetree/services/i-motion-service.hpp"
#include "beetree/startpk/tokens.hpp"

namespace bte {
namespace {
struct Data
{
    Clock::time_point start;
};
}  // namespace

static void setup(Context& context)
{
    auto data = context.get_data<Data>();
    auto svc  = blackboard::update<IMotionService>();
    if (svc)
    {
        data->start = Clock::now();
        svc->stop();
    }
}

static Result loop(Context& context)
{
    auto status = Status::Fail;
    auto data   = context.get_data<Data>();
    auto svc    = blackboard::get<IMotionService>();

    if (svc)
    {
        // fail on 1 second timeout
        if (Clock::elapsed(data->start) < 1_s)
        {
            status = svc->model().is_stopped ? Status::Success : Status::Running;
        }
    }

    return {status};
}

Recipe make_stop()
{
    return Builder(tokens::StopMotionNode, loop).add_data<Data>().add_setup(setup).finalize();
}
}  // namespace bte