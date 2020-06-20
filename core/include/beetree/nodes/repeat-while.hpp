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
/// @return makes the recipe for the `RepeatWhileSuccess` decorator node.
///
Recipe make_repeat_while_success();
///
/// @ingroup make
/// @return makes the recipe for the `RepeatWhileFail` decorator node.
///
Recipe make_repeat_while_fail();

///
/// @ingroup nodes
///
/// RepeatWhileFail Node
/// ====================
///
/// @see RepeatUntilSuccess
///
/// This is a synonym to RepeatUntilSuccess
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
using RepeatWhileFail = Decorator<make_repeat_while_fail>;

///
/// @ingroup nodes
///
/// RepeatWhileSuccess Node
/// =======================
///
/// @see RepeatUntilFail
///
/// This is a synonym to RepeatUntilFail
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
using RepeatWhileSuccess = Decorator<make_repeat_while_success>;
}  // namespace bte