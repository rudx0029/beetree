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
/// @return the recipe for the `succeeder` decorator node.
///
Recipe make_succeeder();

///
/// @ingroup nodes
///
/// Succeeder Node
/// ==============
///
/// The Succeeder decorator invokes its child branch and always returns success when the branch
/// completes, unless otherwise specified below.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr Fail failBranch;
/// constexpr Success successBranch;
///
/// constexpr auto successWhenFailed = Succeeder{failBranch};
/// constexpr auto successAlways = Succeeder{successBranch};
/// ```
///
/// Returns
/// -------
///
/// |                                   |                                   |
/// |-----------------------------------|-----------------------------------|
/// | `Result{Status::Fail}`            | if the branch is invalid.         |
/// | `Result{Status::Running, branch}` | while the child branch is running |
/// | `Result{Status::Success}`         | otherwise                         |
///
using Succeeder = Decorator<make_succeeder>;
}  // namespace bte