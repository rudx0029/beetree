//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"
#include "beetree/nodes/behaviors/rotate-internal.hpp"

namespace bte {

///
/// @ingroup behavior_nodes
///
/// RotateRelative
/// ==============
///
/// The RotateRelative leaf rotates the robot by the target amount of
/// degrees/radians. For example, a target of 10 degrees will rotate the robot
/// 10 degrees CCW and -10 degrees will rotate the robot CW by 10 degrees.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr units::Angle target = 10_deg;
/// constexpr RotateRelative<target> rotate;
/// ```
///
/// Requires
/// --------
///
/// - `INavigationService`
///
/// Parameters
/// ----------
///
/// |        |                                                      |
/// |--------|------------------------------------------------------|
/// | Target | the number of degrees/radians the robot will rotate. |
///
/// Returns
/// -------
///
/// |                           |                                           |
/// |---------------------------|-------------------------------------------|
/// | `Result{Status::Success}` | if the robot made it to its target.       |
/// | `Result{Status::Running}` | when the robot is rotating to the target. |
/// | `Result{Status::Fail}`    | otherwise                                 |
///
template <const units::Angle& Target>
using RotateRelative = Leaf<make_rotate_relative<Target>>;

///
/// @ingroup behavior_nodes
///
/// RotateAbsolute
/// ==============
///
/// The RotateAbsolute leaf rotates the robot to the target heading. For
/// example, specifying a target of 10 degrees when the robot's heading is
/// currently 75 degrees will result in rotating until the robot's heading is 10
/// degrees. This is a relative rotation of -65 degrees.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr units::Angle origin_heading = 0_deg;
/// constexpr RotateAbsolute<origin_heading> rotate;
/// ```
///
/// Requires
/// --------
///
/// - `INavigationService`
///
/// Parameters
/// ----------
///
/// |        |                                   |
/// |--------|-----------------------------------|
/// | Target | the desired heading of the robot. |
///
/// Returns
/// -------
///
/// |                           |                                           |
/// |---------------------------|-------------------------------------------|
/// | `Result{Status::Success}` | if the robot made it to its target.       |
/// | `Result{Status::Running}` | when the robot is rotating to the target. |
/// | `Result{Status::Fail}`    | otherwise                                 |
///
template <const units::Angle& Target>
using RotateAbsolute = Leaf<make_rotate_absolute<Target>>;

///
/// @ingroup behavior_nodes
///
/// RotateRelativeFnc
/// =================
///
/// @see RotateRelative
///
/// The RotateRelative leaf rotates the robot by the target amount of
/// degrees/radians. For example, a target of 10 degrees will rotate the robot
/// 10 degrees CCW and -10 degrees will rotate the robot CW by 10 degrees.
///
/// Usage
/// -----
///
/// ```cpp
/// inline units::Angle target()
///     { return blackboard::get_assert<ILocationService>().model().target; }
/// constexpr RotateRelative<target> rotate;
/// ```
///
/// Requires
/// --------
///
/// - `INavigationService`
///
/// Parameters
/// ----------
///
/// |           |                                                                            |
/// |-----------|----------------------------------------------------------------------------|
/// | TargetFnc | A delegate specifying the number of degrees/radians the robot will rotate. |
///
/// Returns
/// -------
///
/// |                           |                                           |
/// |---------------------------|-------------------------------------------|
/// | `Result{Status::Success}` | if the robot made it to its target.       |
/// | `Result{Status::Running}` | when the robot is rotating to the target. |
/// | `Result{Status::Fail}`    | otherwise                                 |
///
template <units::Angle TargetFnc(void)>
using RotateRelativeFnc = Leaf<make_rotate_relative<TargetFnc>>;

///
/// @ingroup behavior_nodes
///
/// RotateAbsoluteFnc
/// =================
///
/// @see RotateAbsolute
///
/// The RotateAbsoluteFnc leaf rotates the robot to the target heading. For
/// example, specifying a target of 10 degrees when the robot's heading is
/// currently 75 degrees will result in rotating until the robot's heading is 10
/// degrees. This is a relative rotation of -65 degrees.
///
/// Usage
/// -----
///
/// ```cpp
/// inline units::Angle origin_heading()
///     { return blackboard::get_assert<ILocationService>().model.origin; }
/// constexpr RotateAbsolute<origin_heading> rotate;
/// ```
///
/// Requires
/// --------
///
/// - `INavigationService`
///
/// Parameters
/// ----------
///
/// |           |                                                         |
/// |-----------|---------------------------------------------------------|
/// | TargetFnc | A delegate specifying the desired heading of the robot. |
///
/// Returns
/// -------
///
/// |                           |                                           |
/// |---------------------------|-------------------------------------------|
/// | `Result{Status::Success}` | if the robot made it to its target.       |
/// | `Result{Status::Running}` | when the robot is rotating to the target. |
/// | `Result{Status::Fail}`    | otherwise                                 |
///
template <units::Angle TargetFnc(void)>
using RotateAbsoluteFnc = Leaf<make_rotate_absolute<TargetFnc>>;

}  // namespace bte