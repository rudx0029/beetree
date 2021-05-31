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
/// @return the recipe to build the Success node
///
Recipe make_success();

///
/// @ingroup nodes
///
/// Success
/// =======
///
/// The Success leaf immediately returns success and does not perform any action. It is equivalent
/// to the `Null` leaf. The node can be used to help control flow or simply communicate the
///'behavior' of a tree.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr Success success;
/// ```
///
/// Returns
/// -------
///
/// |                           |        |
/// |---------------------------|--------|
/// | `Result{Status::Success}` | always |
///
using Success = Leaf<make_success>;
}  // namespace bte