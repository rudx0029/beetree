//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"
#include "beetree/nodes/behaviors/go-to-absolute-internal.hpp"
#include "beetree/nodes/behaviors/go-to-relative-internal.hpp"

namespace bte {
///
/// @ingroup behavior_nodes
///
/// GoToRelative
/// ============
///
/// The GoToRelative leaf commands and controls the robot to go to a location
/// relative to its current location. For example, if the location is {10_mm,
/// 10_mm} and the robot is at {150_mm, 60_mm}, then the robot will move to the
/// position {160_mm, 70_mm}.
///
/// Usage
/// -----
///
/// ```
/// constexpr units::Coordinate position{10_mm, 10_mm};
/// constexpr GoToRelative<position> go;
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
/// |          |                                                             |
/// |----------|-------------------------------------------------------------|
/// | Position | the relative coordinate to go to from its present location. |
///
/// Returns
/// -------
///
/// |                           |                                                |
/// |---------------------------|------------------------------------------------|
/// | `Result{Status::Success}` | if the robot made it to its position.          |
/// | `Result{Status::Running}` |  when the robot is travelling to the position. |
/// | `Result{Status::Fail}`    | otherwise                                      |
///
template <const units::Coordinate& Position>
using GoToRelative = Leaf<make_go_to_relative<Position>>;

///
/// @ingroup behavior_nodes
///
/// GoToAbsolute
/// ============
///
/// The GoToAbsolute leaf commands and controls the robot to go to an absolute
/// or global location from its current location. For example, if the location
/// is {10_mm, 10_mm} and the robot is at {150_mm, 60_mm}, then the robot will
/// move to the position {10_mm, 10_mm}.
///
/// Usage
/// -----
///
/// ```
/// constexpr units::Coordinate origin{0_mm, 0_mm};
/// constexpr GoToAbsolute<origin> go_home;
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
/// |          |                                                             |
/// |----------|-------------------------------------------------------------|
/// | Position | the absolute coordinate to go to from its present location. |
///
/// Returns
/// -------
///
/// |                           |                                                |
/// |---------------------------|------------------------------------------------|
/// | `Result{Status::Success}` | if the robot made it to its position.          |
/// | `Result{Status::Running}` |  when the robot is travelling to the position. |
/// | `Result{Status::Fail}`    | otherwise                                      |
///
template <const units::Coordinate& Position>
using GoToAbsolute = Leaf<make_go_to_absolute<Position>>;

///
/// @ingroup behavior_nodes
///
/// GoTo
/// ====
///
/// @see GoToAbsolute
///
/// The GoTo leaf commands and controls the robot to go to an absolute
/// or global location from its current location using a dynamic parmeter, i.e.
/// a function generating absolute coordinates.
///
/// Usage
/// -----
///
/// ```
/// inline units::Coordinate origin()
///   { return services::location<ILocationService>()->model().origin; }
/// constexpr GoToRelative<origin> go_home;
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
/// |          |                                                                     |
/// |----------|---------------------------------------------------------------------|
/// | Position | the dynamic parameter specifying absolute coordinates when invoked. |
///
/// >  The function is only invoked once when the node is setup.
///
/// Returns
/// -------
///
/// |                           |                                                |
/// |---------------------------|------------------------------------------------|
/// | `Result{Status::Success}` | if the robot made it to its position.          |
/// | `Result{Status::Running}` |  when the robot is travelling to the position. |
/// | `Result{Status::Fail}`    | otherwise                                      |
///
template <units::Coordinate PositionFnc(void)>
using GoTo = Leaf<make_go_to_absolute<PositionFnc>>;
}  // namespace bte