//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include "beetree/engine/status.hpp"

namespace bte {
/// The result after one step of the engine.
struct EngineResult
{
    /// The current status of the node.
    Status node_status;
    /// True if the current visited node is a leaf and it is executing
    /// multiple times.
    bool is_running_leaf;
    /// True if the tree has been fully traversed.
    bool all_visited;
};
}  // namespace bte