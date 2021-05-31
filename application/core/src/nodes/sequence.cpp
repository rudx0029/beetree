//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/nodes/sequence.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/engine/branch-reader.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"

namespace bte {
namespace {
using BranchIterator = BranchReader::const_iterator;

struct Data
{
    Status status = Status::Fail;  // stays running until branch indicates
                                   // Fail or there are no more branches
    BranchIterator iter = nullptr;
};
}  // namespace

static void setup(Context& context)
{
    BranchIterator iter = BranchReader::begin(context.get_node());
    Data*          data = context.get_data<Data>();

    data->status = iter ? Status::Running : Status::Fail;
    data->iter   = iter;
}

static Result loop(Context& context)
{
    Status      status = Status::Fail;
    Data*       data   = context.get_data<Data>();
    const Node* branch = nullptr;

    if (data->iter)
    {
        if (Status::Running == data->status)
        {
            if (data->iter != BranchReader::end(context.get_node()))
            {
                status = data->status;
                branch = *data->iter;
                data->iter++;
            }
            else
            {
                // we're at the end and still running
                // - we have successful made it through all of the nodes
                status = Status::Success;
                branch = nullptr;
            }
        }
        else
        {
            // we are done, assign to the final status (should be fail)
            status = data->status;
        }
    }

    return {status, branch};
}

static void on_branch_complete(Status branch_status, Context& context)
{
    if (Status::Fail == branch_status)
    {
        context.get_data<Data>()->status = Status::Fail;
    }
}

Recipe make_sequence()
{
    return Builder(tokens::SequenceNode, loop)
        .add_data<Data>()
        .add_setup(setup)
        .add_handler(on_branch_complete)
        .finalize();
}
}  // namespace bte