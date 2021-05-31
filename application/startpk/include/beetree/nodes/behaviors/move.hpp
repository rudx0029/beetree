//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"
#include "beetree/nodes/behaviors/move-internal.hpp"

namespace bte {
///
/// @ingroup behavior_nodes
///
/// Move
/// ====
///
/// The Move leaf sets the robots motion profile, i.e. velocity, acceleration,
/// and angular velocity and returns immediately.
///
/// Usage
/// -----
///
/// ```
/// constexpr units::MotionProfile straight{200_mmps, 0_mpss, 0_radps};
/// constexpr Move<straight> move;
/// ```
///
/// Requires
/// --------
///
/// - `IMotionService`
///
/// Parameters
/// ----------
///
/// |        |                               |
/// |--------|-------------------------------|
/// | Motion | the commanded motion profile. |
///
/// Returns
/// -------
///
/// |                           |                                       |
/// |---------------------------|---------------------------------------|
/// | `Result{Status::Success}` | after commanding the robot's motion.  |
/// | `Result{Status::Fail}`    | if the motion service is unavailable. |
///
template <const units::MotionProfile& Motion>
using Move = Leaf<make_move<Motion>>;

}  // namespace bte