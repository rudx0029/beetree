//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/nodes/repeat-until.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/engine/branch-reader.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/nodes/repeat-while.hpp"

namespace bte {
namespace {
using BranchIterator = BranchReader::const_iterator;
struct Data
{
    Status repeat_until;
    Status status;
};
}  // namespace

static void setup(Context& context, Status repeat_until)
{
    BranchIterator iter = BranchReader::begin(context.get_node());
    Data*          data = context.get_data<Data>();

    data->repeat_until = repeat_until;
    data->status       = Status::Fail;

    if (iter)
    {
        data->status = Status::Running;
    }
}

template <Status REPEAT_UNTIL>
static void setup(Context& context)
{
    setup(context, REPEAT_UNTIL);
}

static Result loop(Context& context)
{
    BranchIterator iter = BranchReader::begin(context.get_node());
    Data*          data = context.get_data<Data>();

    return iter ? Result{data->status, *iter} : Result{Status::Fail};
}

static void on_branch_complete(Status branch_status, Context& context)
{
    Data* data = context.get_data<Data>();
    if (branch_status == data->repeat_until)
    {
        data->status = branch_status;
    }
}

static Recipe get_recipe(delegate::Setup s, TraceToken token)
{
    return Builder(token, loop)
        .add_data<Data>()
        .add_setup(s)
        .add_handler(on_branch_complete)
        .finalize();
}

//-----------------------------------------------------------------------------
Recipe make_repeat_until_success()
{
    return get_recipe(setup<Status::Success>, tokens::RepeatUntilSuccessNode);
}
//-----------------------------------------------------------------------------
Recipe make_repeat_until_fail()
{
    return get_recipe(setup<Status::Fail>, tokens::RepeatUntilFailNode);
}
//-----------------------------------------------------------------------------
Recipe make_repeat_while_fail()
{
    return get_recipe(setup<Status::Success>, tokens::RepeatWhileFailNode);
}
//-----------------------------------------------------------------------------
Recipe make_repeat_while_success()
{
    return get_recipe(setup<Status::Fail>, tokens::RepeatWhileSuccessNode);
}
//-----------------------------------------------------------------------------

}  // namespace bte