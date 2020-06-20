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
/// @return the recipe to build the Null node
///
Recipe make_null();

///
/// @ingroup nodes
/// Null
/// ====
///
/// The Null leaf does nothing, except return success. It is equivalent to the
/// `Success` leaf.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr Null null;
/// ```
///
/// Returns
/// -------
///
/// |                           |        |
/// |---------------------------|--------|
/// | `Result{Status::Success}` | always |
///
using Null = Leaf<make_null>;
}  // namespace bte