///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/engine/node.hpp"
#include "beetree/engine/result.hpp"

namespace bte {
struct SelectAlgorithm
{
    struct Data
    {
        Status               status = Status::Running;
        Node::const_iterator iter   = nullptr;
    };

    static void   setup(const Node& node, /*in,out*/ Data& data);
    static Result loop(const Node& node, /*in,out*/ Data& data);
    static void   update(Status branch_status, /*in,out*/ Data& data);
};
}  // namespace bte