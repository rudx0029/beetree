//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/nodes/inverter.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/engine/branch-reader.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"

namespace bte {
namespace {
using BranchIterator = BranchReader::const_iterator;

struct Data
{
    Status status;
};
}  // namespace

// The only internal state of the node is storing the branches status.
// Therefore construct the state as the Status type.
static void setup(Context& ctx)
{
    Data* data          = ctx.get_data<Data>();
    data->status        = Status::Fail;
    BranchIterator iter = BranchReader::begin(ctx.get_node());

    if (iter)
    {
        data->status = Status::Running;
    }
}

static Result loop(Context& ctx)
{
    Data*          data = ctx.get_data<Data>();
    Result         result{Status::Fail};
    BranchIterator iter = BranchReader::begin(ctx.get_node());

    if (iter)
    {
        result = {data->status, *iter};
    }

    return result;
}

static void on_branch_complete(Status branch_status, Context& ctx)
{
    Data* data = ctx.get_data<Data>();
    switch (branch_status)
    {
        case Status::Success:
            data->status = Status::Fail;
            break;
        case Status::Fail:
            data->status = Status::Success;
            break;
        case Status::Running:
            // do nothing;
            break;
    }
}

Recipe make_inverter()
{
    return Builder(tokens::InverterNode, loop)
        .add_data<Data>()
        .add_setup(setup)
        .add_handler(on_branch_complete)
        .finalize();
}
}  // namespace bte