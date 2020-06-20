///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#pragma once
#include "beetree/engine/status.hpp"

namespace bte {
struct Node;  // forward declaration

struct Result
{
    Status      status;
    const Node* branch;

    Result(Status s) : status(s), branch(nullptr) {}
    Result(Status s, const Node* b) : status(s), branch(b) {}
};
}  // namespace bte