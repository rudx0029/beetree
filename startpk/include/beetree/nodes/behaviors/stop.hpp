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
/// @ingroup make
/// @return recipe to build Stop leaf
///
Recipe make_stop();

///
/// @ingroup behavior_nodes
///
/// Stop
/// ====
///
/// The Stop leaf initiates a stop command, i.e. zeroing velocities and
/// acceleration, and waits for the robot to come to a stop. If the robot does
/// not stop after 1 second, the leaf fails.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr Stop stop;
/// ```
///
/// Requires
/// --------
///
/// - `IMotionService`
///
/// Returns
/// -------
///
/// |                           |                              |
/// |---------------------------|------------------------------|
/// | `Result{Status::Success}` | when the robot stops.        |
/// | `Result{Status::Running}` | while the robot is stopping. |
/// | `Result{Status::Fail}`    | otherwise                    |
///
using Stop = Leaf<make_stop>;

}  // namespace bte