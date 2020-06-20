//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/nodes/repeat-for.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/engine/branch-reader.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"

namespace bte {
namespace {
using BranchIterator = BranchReader::const_iterator;

struct Data
{
    Status   status;
    uint32_t cur_rep;
    uint32_t num_reps;
};
}  // namespace

void setup_repeat_for(Context& context, std::size_t num_reps)
{
    BranchIterator iter = BranchReader::begin(context.get_node());
    Data*          data = context.get_data<Data>();

    data->num_reps = num_reps;
    data->cur_rep  = 0;
    data->status   = Status::Running;

    if (!iter)
    {
        data->status = Status::Fail;
    }
    else if (0 == num_reps)
    {
        data->status = Status::Success;
    }
}

static Result loop(Context& context)
{
    BranchIterator iter = BranchReader::begin(context.get_node());
    Data*          data = context.get_data<Data>();

    // continue to return the current status and branch
    return iter ? Result{data->status, *iter} : Result{Status::Fail};
}

static void on_branch_complete(Status status, Context& context)
{
    auto data = context.get_data<Data>();

    data->cur_rep++;

    if (status == Status::Fail)
    {
        data->status = status;
    }
    else if (data->cur_rep >= data->num_reps)
    {
        data->status = status;
    }
}

static void on_trace(TraceStream& stream, Context& context)
{
    Data* data = context.get_data<Data>();
    stream << data->num_reps;
}

Recipe make_repeat_for(delegate::Setup s)
{
    return Builder(tokens::RepeatForNode, loop)
        .add_data<Data>()
        .add_setup(s)
        .add_handler(on_branch_complete)
        .add_handler(on_trace)
        .finalize();
}
}  // namespace bte