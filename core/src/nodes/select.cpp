//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/nodes/select.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/engine/select-algorithm.hpp"

namespace bte {
namespace {
using Data = SelectAlgorithm::Data;
}

static void setup(Context& context)
{
    SelectAlgorithm::setup(context.get_node(), *context.get_data<Data>());
}

static Result loop(Context& context)
{
    return SelectAlgorithm::loop(context.get_node(), *context.get_data<Data>());
}

static void on_branch_complete(Status s, Context& context)
{
    SelectAlgorithm::update(s, *context.get_data<Data>());
}

Recipe make_select()
{
    return Builder(tokens::SelectNode, loop)
        .add_data<Data>()
        .add_setup(setup)
        .add_handler(on_branch_complete)
        .finalize();
}
}  // namespace bte