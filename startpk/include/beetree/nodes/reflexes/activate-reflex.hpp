//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <type_traits>
#include "beetree/nodes/action.hpp"
#include "beetree/services/api/reflexes-api.hpp"
#include "beetree/startpk/tokens.hpp"

namespace bte {

///
/// @ingroup reflex_nodes
///
/// ActivateReflex
/// ==============
///
/// An `Action` node that activates the reflex `R` when visited.
///
/// @see Action
/// @see ReflexesAPI::activate
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr ActivateReflex<simple_reflex_ids::BUMP_REFLEX> activateBumpReflex;
/// ```
///
/// Parameters
/// ----------
///
/// |   |                                                         |
/// |---|---------------------------------------------------------|
/// | R | The reflex to activate.                                 |
/// | T | An optional token describing which reflex is activated. |
///
template <const Reflex& R, const TraceToken& T = tokens::ActivateReflexNode>
using ActivateReflex = Action<ReflexesAPI::activate<R>, T>;

///
/// @ingroup reflex_nodes
///
/// ActivateReflexFnc
/// =================
///
/// An `Action` node that activates the named reflex dynamically through the delegate `FNC`.
///
/// @see Action
/// @see ReflexesAPI::activate
///
/// Usage
/// -----
///
/// ```cpp
/// inline Reflex get_current_reflex(){ return simple_reflex_ids::BUMP_REFLEX; } constexpr
/// ActivateReflexFnc<get_reflex> activateCurrentReflex;
/// ```
///
/// Parameters
/// ----------
///
/// |     |                                                         |
/// |-----|---------------------------------------------------------|
/// | FNC | A delegate returning the reflex to activate.            |
/// | T   | An optional token describing which reflex is activated. |
///
template <ReflexesAPI::GetReflexFnc FNC, const TraceToken& T = tokens::ActivateReflexNode>
using ActivateReflexFnc = Action<ReflexesAPI::activate<FNC>, T>;

///
/// @ingroup reflex_nodes
///
/// DeactivateAllReflexes
/// =====================
///
/// An `Action` node that deactivates all reflexes when visited.
///
/// @see Action
/// @see ReflexesAPI::deactivate_all
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr DeactivateAllReflexes deactivateAllReflexes;
/// ```
///
using DeactivateAllReflexes =
    Action<ReflexesAPI::deactivate_all, tokens::DeactivateAllReflexesNode>;
}  // namespace bte