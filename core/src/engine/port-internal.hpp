///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/engine/context.hpp"
#include "beetree/engine/node.hpp"
#include "beetree/engine/status.hpp"

namespace bte {
// > STATE DEFINITION
struct PortData
{
    Status      status   = Status::Fail;
    const Node* sub_tree = nullptr;
};

// to be used by the engine

namespace internal {
void port_setup(Context& ctx, const Node* connection, bool is_mandatory);
}
}  // namespace bte