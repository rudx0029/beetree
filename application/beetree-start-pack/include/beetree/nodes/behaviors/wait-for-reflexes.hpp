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
/// @return the recipe to build the WaitForReflexes leaf
///
Recipe make_wait_for_reflexes();

///
/// @ingroup utility_nodes
///
/// WaitForReflexes
/// ===============
///
/// The WaitForReflexes leaf waits indefinitely for an active reflex to complete
/// before returning. The leaf should be used in a 'behaviors' tree that
/// receives reflex exceptions to suspend any activity while the reflex is
/// being handled in another tree.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr WaitForReflexes waitForReflexes;
///
/// constexpr units::Coordinate origin{0_m, 0_m};
/// constexpr GoToAbsolute<origin> goToOrigin;
///
/// constexpr auto tryGoToOriginBranches = branches(goToOrigin, waitForReflexes);
/// constexpr auto tryGoToOrigin = TryCatchReflex{tryGoToOriginBranches};
/// ```
///
/// Requires
/// --------
///
/// - IReflexesService
///
/// Returns
/// -------
///
/// |                           |                                                |
/// |---------------------------|------------------------------------------------|
/// | `Result{Status::Running}` | while waiting for an active reflex to complete |
/// | `Result{Status::Fail}`    | the reflex service is not available           |
/// | `Result{Status::Success}` | otherwise                                      |
///
///
using WaitForReflexes = Leaf<make_wait_for_reflexes>;

}  // namespace bte