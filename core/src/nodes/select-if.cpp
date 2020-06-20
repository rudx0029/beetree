//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/nodes/select-if.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/engine/branch-reader.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"

namespace bte {
namespace {
using BranchIterator = BranchReader::const_iterator;
}

static void setup(Context& c)
{
    Status*        status = c.get_data<Status>();
    BranchIterator iter   = BranchReader::begin(c.get_node());

    if (iter)
    {
        *status = Status::Running;
    }
    else
    {
        *status = Status::Fail;
    }
}

Result loop_select_if(Context& c, delegate::Predicate pred)
{
    Status*        status = c.get_data<Status>();
    Result         result{Status::Fail};
    BranchIterator iter = BranchReader::begin(c.get_node());

    if (iter && pred)
    {
        if (*status == Status::Running)
        {
            bool select_branch = pred();
            if (!select_branch)
            {
                *status = Status::Fail;
            }
        }
        result = {*status, *iter};
    }

    return result;
}

static void on_branch_complete(Status branch_status, Context& c)
{
    Status* status = c.get_data<Status>();
    *status        = branch_status;
}

Recipe make_select_if(delegate::Loop loop)
{
    return Builder(tokens::SelectIfNode, loop)
        .add_data<Status>()
        .add_setup(setup)
        .add_handler(on_branch_complete)
        .finalize();
}

}  // namespace bte