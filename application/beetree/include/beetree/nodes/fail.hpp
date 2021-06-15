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
/// @return the recipe to build the Fail node
///
Recipe make_fail();

///
/// @ingroup nodes
///
/// Fail
/// ====
///
/// The Fail leaf immediately returns fail and does not perform any
/// action. The node can be used to help control flow or simply communicate the
///'behavior' of a tree.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr Fail fail;
/// ```
///
/// Returns
/// -------
///
/// |                           |        |
/// |---------------------------|--------|
/// | `Result{Status::Fail}`    | always |
///
using Fail = Leaf<make_fail>;

}  // namespace bte