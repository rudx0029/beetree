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
/// @return the recipe to build the Toggle Debug LED node
///
Recipe make_toggle_debug_led();

///
/// @ingroup nodes
///
/// ToggleDebugLED Node
/// ===================
///
/// The ToggleDebugLED leaf toggles the LED specified by the debug service interface
/// (IDebugService). If the interface can not be located, then no action occurs.
///
/// Use this node to toggle an LED in areas of the tree that are of interest.
///
/// Usage
/// -----
///
/// ```cpp
/// // application install
/// services::install<IDebugService>(yourDebugServiceInstance);
///
/// // In a tree
/// constexpr ToggleDebugLED toggleLED;
/// ```
///
/// Requires
/// --------
///
/// - `IDebugService`
///
/// Returns
/// -------
///
/// |  |  |
/// |---------------------------|--------|
/// | `Result{Status::Success}` | always |
///
using ToggleDebugLED = Leaf<make_toggle_debug_led>;
}  // namespace bte