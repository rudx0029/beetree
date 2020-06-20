//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/engine/try-catch.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/engine/branch-reader.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "try-catch-internal.hpp"

namespace bte {
namespace internal {

using BranchIterator = BranchReader::const_iterator;

bool is_try_catch_node(const Node& n)
{
    bool is_try_catch = false;

    auto fnc = n.build;
    if ((fnc == try_catch_all) || (fnc == try_catch_reflex) || (fnc == try_catch_user))
    {
        is_try_catch = true;
    }

    return is_try_catch;
}

bool is_try_catch_node_strict(const Node& n, ExceptionType ex)
{
    bool is_try_catch = false;

    auto fnc = n.build;
    if ((fnc == try_catch_all) || (fnc == try_catch_reflex && ex == ExceptionType::REFLEX) ||
        (fnc == try_catch_user && ex == ExceptionType::USER))
    {
        is_try_catch = true;
    }

    return is_try_catch;
}

bool is_try_active(TryCatchData* data, const Context& context)
{
    BranchIterator branch_end = BranchReader::end(context.get_node());
    return data && data->iter && branch_end && (data->iter != branch_end);
}

bool is_catch_active(TryCatchData* data, const Context& context)
{
    BranchIterator branch_end = BranchReader::end(context.get_node());
    return data && data->iter && branch_end && (data->iter == branch_end);
}
}  // namespace internal

using internal::TryCatchData;

static void setup(Context& c)
{
    TryCatchData* data = c.get_data<TryCatchData>();
    SelectAlgorithm::setup(c.get_node(), *data);
}

static Result loop(Context& c)
{
    // A try catch node is simply a select node
    // - use the select algorthm
    TryCatchData* data = c.get_data<TryCatchData>();
    return SelectAlgorithm::loop(c.get_node(), *data);
}

static void on_branch_complete(Status status, Context& c)
{
    // The try catch node retires when its try or catch branch completes.
    // When the try branch completes, the node retires and does not activate
    // the catch branch.
    // > assumption: there is 1 try branch and 1 catch branch
    TryCatchData* data = c.get_data<TryCatchData>();
    if (data)
    {
        data->status = status;
    }
}
static void on_exception(const Exception& ex, Context& c)
{
    // Try catch uses the select algorithm, so indicate a failed status to
    // get the next node
    TryCatchData* data = c.get_data<TryCatchData>();
    SelectAlgorithm::update(Status::Fail, *data);
}

static Recipe make_recipe()
{
    return Builder(tokens::TryCatchNode, loop)
        .add_data<TryCatchData>()
        .add_setup(setup)
        .add_handler(on_branch_complete)
        .add_handler(on_exception)
        .finalize();
}

Recipe try_catch_all() { return make_recipe(); }

Recipe try_catch_reflex() { return make_recipe(); }

Recipe try_catch_user() { return make_recipe(); }
}  // namespace bte