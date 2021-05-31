//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/node.hpp"

namespace bte {

///
/// @ingroup make
/// @return the recipe for the `inverter` decorator node.
///
Recipe make_inverter();

///
/// @ingroup nodes
///
/// Inverter Node
/// =============
///
/// The inverter inverts the result of its branch.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr Fail failBranch;
/// constexpr Success successBranch;
///
/// constexpr auto invertedToSuccess = Inverter{failBranch};
/// constexpr auto invertedToFail = Inverter{successBranch};
/// ```
///
/// Returns
/// -------
///
/// |                                   |                                  |
/// |-----------------------------------|----------------------------------|
/// | `Result{Status::Success}`         | when it's branch returns fail    |
/// | `Result{Status::Running, branch}` | while it's branch is running.    |
/// | `Result{Status::Fail}`            | when it's branch returns success |
/// | `Result{Status::Fail}`            | if the branch is invalid         |
///
using Inverter = Decorator<make_inverter>;
}  // namespace bte