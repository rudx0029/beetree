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
///
/// @return recipe for the NullOdometry leaf.
///
Recipe make_null_odometry();

///
/// @ingroup utility_nodes
///
/// NullOdometry
/// ============
///
/// The `NullOdometry` leaf signals to reset the robot's odometry by invoking the navigation
/// service.
///
/// Usage
/// -----
///
/// ```
/// constexpr NullOdometry nullOdometry;
/// ```
///
/// Requires
/// --------
///
/// - INavigationService
///
/// Returns
/// -------
///
/// |                           |                                           |
/// |---------------------------|-------------------------------------------|
/// | `Result{Status::Fail}`    | if the navigation service is unavailable. |
/// | `Result{Status::Success}` | otherwise                                 |
///
///
using NullOdometry = Leaf<make_null_odometry>;

}  // namespace bte