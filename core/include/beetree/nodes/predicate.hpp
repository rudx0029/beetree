//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/nodes/predicate-internal.hpp"

namespace bte {

///
/// @ingroup nodes
///
/// Predicate
/// ---------
///
/// The Predicate leaf invokes a given delegate and returns Success if the
/// delegate returns true. If the delegate returns false or is an invalid
/// delegate, the leaf returns Fail. You can use this leaf to dynamically
/// control the flow using predicate type delegates.
///
/// Usage
/// -----
///
/// ```cpp
/// // The is_stopped delegate checks if the robot has stopped.
/// inline void is_stopped()
///   { return blackboard::get_assert<IMotionService>().model().is_stopped; }
///
/// // Turn the delegate into a node and add it to a tree
/// // Optionally a token can be added to give the node a unique name other than
/// // 'predicate'
/// constexpr Predicate<is_stopped> isStopped;
/// ```
///
///
/// Parameters
/// ----------
///
/// |   |                                                            |
/// |---|------------------------------------------------------------|
/// | P | the predicate to invoke when the node is visited           |
/// | T | the name of the node defaulting to the generic 'predicate' |
///
/// Returns
/// -------
///
/// |                           |                                  |
/// |---------------------------|----------------------------------|
/// | `Result{Status::Success}` | when the predicate returns true  |
/// | `Result{Status::Fail}`    | when the predicate returns false |
/// | `Result{Status::Fail}`    | when the predicate is invalid    |
///
template <delegate::Predicate P, const TraceToken& T = tokens::PredicateNode>
using Predicate = Leaf<make_predicate<P, T>>;
}  // namespace bte