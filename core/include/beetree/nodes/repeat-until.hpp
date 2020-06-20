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
/// @return makes the recipe for the `RepeatUntilSuccess` decorator node.
///
Recipe make_repeat_until_success();
///
/// @ingroup make
/// @return makes the recipe for the `RepeatUntilFail` decorator node.
///
Recipe make_repeat_until_fail();

///
/// @ingroup nodes
///
/// RepeatUntilSuccess Node
/// =======================
///
/// The RepeatUntilSuccess decorator will repeatedly visit and invoke it's
/// branch until the branch returns success. If the branch is invalid the node
/// will return immediately with fail.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr Fail failBranch;
/// constexpr Success successBranch;
///
/// constexpr auto executesBranchForever = RepeatUntilSuccess{failBranch};
/// constexpr auto executesAndReturnsSuccess = RepeatUntilSuccess{successBranch};
/// ```
///
/// Returns
/// -------
///
/// |                                   |                                           |
/// |-----------------------------------|-------------------------------------------|
/// | `Result{Status::Success}`         | when it's branch returns success          |
/// | `Result{Status::Running, branch}` | while the branch repeatedly returns fail. |
/// | `Result{Status::Fail}`            | if the branch is invalid                  |
///
using RepeatUntilSuccess = Decorator<make_repeat_until_success>;

///
/// @ingroup nodes
///
/// RepeatUntilFail Node
/// =======================
///
/// The RepeatUntilFail decorator will repeatedly visit and invoke it's
/// branch until the branch returns fail. If the branch is invalid the node
/// will return immediately with fail.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr Fail failBranch;
/// constexpr Success successBranch;
///
/// constexpr auto executesAndReturnsFail = RepeatUntilFail{failBranch};
/// constexpr auto executesBranchForever = RepeatUntilFail{successBranch};
/// ```
///
/// Returns
/// -------
///
/// |                                   |                                              |
/// |-----------------------------------|----------------------------------------------|
/// | `Result{Status::Fail}`            | when the branch returns fail                 |
/// | `Result{Status::Fail}`            | if the branch is invalid                     |
/// | `Result{Status::Running, branch}` | while the branch repeatedly returns success. |
///
using RepeatUntilFail = Decorator<make_repeat_until_fail>;
}  // namespace bte