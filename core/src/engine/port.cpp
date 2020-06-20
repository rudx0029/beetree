///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "beetree/engine/port.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/engine/result.hpp"

#include "port-internal.hpp"

namespace bte {
// > LOOP
static Result loop(Context& c)
{
    Result    result{Status::Fail};
    PortData* data = c.get_data<PortData>();
    if (data)
    {
        result = {data->status, data->sub_tree};
    }
    return result;
}

// > ADDITIONAL HANDLERS
static void on_branch_complete(Status s, Context& c)
{
    // simply save the (child node) branches status and return it in the
    // loop
    PortData* data = c.get_data<PortData>();
    if (data)
    {
        data->status = s;
    }
}

// > RECIPE BUILDER
static Recipe make_recipe()
{
    return Builder(tokens::PortNode, loop)
        .add_data<PortData>()
        .add_handler(on_branch_complete)
        .finalize();
}

namespace internal {
/// This setup method is invoked directly in the engine instead
/// of calling the method supplied in the recipe. It facilitates
/// creating and traveling to the connected node specified by the
/// connection links
void port_setup(Context& c, const Node* connection, bool is_mandatory)
{
    // setup the port by constructing the node's state and setting it up
    // appropriately
    PortData* data = c.get_data<PortData>();
    if (connection)
    {
        data->status   = Status::Running;
        data->sub_tree = connection;
    }
    else
    {
        data->status   = is_mandatory ? Status::Fail : Status::Success;
        data->sub_tree = nullptr;
    }
}
}  // namespace internal

Recipe port_mandatory() { return make_recipe(); }
Recipe port_optional() { return make_recipe(); }

}  // namespace bte