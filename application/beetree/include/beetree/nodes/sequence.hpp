//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"

namespace bte {
///
/// @return the recipe for the `sequence` composite node.
///
Recipe make_sequence();

///
/// @ingroup nodes
///
/// Sequence Node
/// =============
///
/// The Sequence node invokes each of its branches until one of its branches
/// returns Fail. This provides an AND operation across its branches.
///
/// Usage
/// ---------
///
/// ```cpp
/// constexpr auto sequenceBranches = branches(node_a, node_b, node_c);
/// constexpr auto sequenceNode = Sequence{sequenceBranches};
/// ```
///
/// Returns
/// -------
///
/// |                                   |                                         |
/// |-----------------------------------|-----------------------------------------|
/// | `Result{Status::Success}`         | if all of its branches returns success. |
/// | `Result{Status::Fail}`            | if any of its branches fail.            |
/// | `Result{Status::Running, branch}` | while any of its branches are invoked.  |
///
using Sequence = Composite<make_sequence>;

}  // namespace bte