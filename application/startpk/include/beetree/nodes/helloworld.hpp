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
/// @return recipe for HelloWorld leaf.
///
Recipe make_helloworld();

///
/// HelloWorld
/// ==========
///
/// The HelloWorld leaf provides no behavior. When it is visited, it'll be
/// recorded in BeeView and shown in the tree display.
///
/// See the contents of `helloworld.cpp` for more in-depth information on the
/// node.
///
/// Usage
/// ---------
///
/// ```cpp
/// constexpr HelloWorld helloWorld;
/// ```
///
/// Returns
/// -------
///
/// |                           |        |
/// |---------------------------|--------|
/// | `Result{Status::Success}` | Always |
///
using HelloWorld = Leaf<make_helloworld>;
}  // namespace bte