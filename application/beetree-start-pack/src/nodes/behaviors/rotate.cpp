#include "beetree/nodes/behaviors/rotate.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/nodes/blackboard.hpp"
#include "beetree/services/i-navigation-service.hpp"
#include "beetree/startpk/tokens.hpp"
#include "beetree/units/methods.hpp"

namespace bte {
namespace {
using units::Angle;
using units::as;
using units::mdeg;

struct Data
{
    Angle target;  // for trace only
    Task  task;
};
}  // namespace

void setup_rotate_relative(Context& c, Angle target)
{
    Data* data   = c.get_data<Data>();
    data->target = target;  // save for trace

    auto svc = blackboard::update<INavigationService>();
    if (svc)
    {
        Angle abs_target = to_abs_heading(target, svc->model().measured_pose);
        // invoke the task and save it
        data->task = svc->rotate_to(abs_target, 20_s);
    }
}
void setup_rotate_absolute(Context& c, Angle target)
{
    Data* data   = c.get_data<Data>();
    data->target = target;  // save for trace

    auto svc = blackboard::update<INavigationService>();
    if (svc)
    {
        // invoke the task and save it
        data->task = svc->rotate_to(target, 20_s);
    }
}

Result loop(Context& c)
{
    Status status = Status::Running;
    Data*  d      = c.get_data<Data>();

    if (!d->task.run())
    {
        status = d->task.is_okay() ? Status::Success : Status::Fail;
        trace::debug(tokens::RotateEnd) << d->task.is_okay();
    }

    return status;
}

void on_trace(TraceStream& s, Context& c)
{
    Data* data = c.get_data<Data>();
    s << as<mdeg>(data->target);
}

Recipe make_rotate_relative(delegate::Setup s)
{
    return Builder(tokens::TurnInPlaceRelativeNode, loop)
        .add_data<Data>()
        .add_setup(s)
        .add_handler(on_trace)
        .finalize();
}

Recipe make_rotate_absolute(delegate::Setup s)
{
    return Builder(tokens::TurnInPlaceAbsoluteNode, loop)
        .add_data<Data>()
        .add_setup(s)
        .add_handler(on_trace)
        .finalize();
}
}  // namespace bte