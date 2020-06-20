//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/core/tokens.hpp"
#include "beetree/nodes/action-internal.hpp"

namespace bte {
///
/// @ingroup nodes
///
/// Action
/// ======
///
/// The Action leaf invokes a given delegate and always returns Success. You can
/// use this leaf to invoke a simple and *quick* action in a tree without
/// implementing a node.
///
/// Usage
/// -----
///
/// ```cpp
///
/// // The move_forward delegate commands the robot to move forward at a rate of 200 mmps.
/// inline void move_forward()
///  { blackboard::update_assert<IMotionService>().move({200_mmps, 0_mpss, 0_radps}); }
///
/// // Turn the delegate into a node and add it to a tree
/// // Optionally a token can be added to give the node a unique name other than 'Action'
/// constexpr Action<move_forward> moveForward;
/// ```
///
/// Parameters
/// ----------
///
/// |   |                                                         |
/// |---|---------------------------------------------------------|
/// | A | the action to invoke when the node is visited           |
/// | T | the name of the node defaulting to the generic 'action' |
///
/// Returns
/// -------
///
/// |                           |        |
/// |---------------------------|--------|
/// | `Result{Status::Success}` | always |
///
template <delegate::Action A, const TraceToken& T = tokens::ActionNode>
using Action = Leaf<make_action<A, T>>;
}  // namespace bte