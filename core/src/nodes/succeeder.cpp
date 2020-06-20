//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/nodes/succeeder.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/engine/branch-reader.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/engine/result.hpp"

namespace bte {
namespace {
using BranchIterator = BranchReader::const_iterator;

struct Data
{
    Status status;
};
}  // namespace

static void setup(Context& context)
{
    Data*          data = context.get_data<Data>();
    BranchIterator iter = BranchReader::begin(context.get_node());

    data->status = Status::Fail;
    if (iter)
    {
        data->status = Status::Running;
    }
}

static Result loop(Context& context)
{
    Data*          data = context.get_data<Data>();
    BranchIterator iter = BranchReader::begin(context.get_node());

    return (iter) ? Result{data->status, *iter} : Result{Status::Fail};
}

static void on_branch_complete(Status branch_status, Context& context)
{
    Data* data = context.get_data<Data>();

    if (branch_status != Status::Running)
    {
        data->status = Status::Success;
    }
}

Recipe make_succeeder()
{
    return Builder(tokens::SucceederNode, loop)
        .add_data<Data>()
        .add_setup(setup)
        .add_handler(on_branch_complete)
        .finalize();
}
}  // namespace bte