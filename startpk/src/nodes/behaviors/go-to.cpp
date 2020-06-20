//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/nodes/behaviors/go-to.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/nodes/blackboard.hpp"
#include "beetree/services/i-navigation-service.hpp"
#include "beetree/startpk/tokens.hpp"
#include "beetree/units/methods.hpp"

namespace bte {
namespace {
using units::as;
using units::Coordinate;
using units::mm;

struct Data
{
    Coordinate target;  // only used for tracing
    Task       task;
};
}  // namespace

void setup_go_to_relative(Context& c, const Coordinate& target)
{
    Data* d   = c.get_data<Data>();
    d->target = target;  // save the original target

    auto svc = blackboard::update<INavigationService>();
    if (svc)
    {
        Coordinate abs_target = to_abs_coord(target, svc->model().measured_pose);
        d->task               = svc->go_to(abs_target, 20_s);
    }
}

void setup_go_to_absolute(Context& c, const Coordinate& target)
{
    Data* d   = c.get_data<Data>();
    d->target = target;  // save the original target

    auto svc = blackboard::update<INavigationService>();
    if (svc)
    {
        d->task = svc->go_to(target, 20_s);
    }
}

static Result loop(Context& c)
{
    auto d = c.get_data<Data>();

    Status status = Status::Running;
    if (!d->task.run())
    {
        status = d->task.is_okay() ? Status::Success : Status::Fail;
        trace::debug(tokens::GotoEnd) << d->task.is_okay();
    }
    return {status};
}

static void on_trace(TraceStream& stream, Context& c)
{
    auto d = c.get_data<Data>();
    stream << as<mm>(d->target.x) << as<mm>(d->target.y);
}

Recipe make_go_to_relative(delegate::Setup s)
{
    return Builder(tokens::GoToPositionRelativeNode, loop)
        .add_data<Data>()
        .add_setup(s)
        .add_handler(on_trace)
        .finalize();
}

Recipe make_go_to_absolute(delegate::Setup s)
{
    return Builder(tokens::GoToPositionAbsoluteNode, loop)
        .add_data<Data>()
        .add_setup(s)
        .add_handler(on_trace)
        .finalize();
}
}  // namespace bte