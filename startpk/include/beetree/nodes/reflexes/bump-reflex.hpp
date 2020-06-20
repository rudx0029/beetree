//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include "beetree/nodes/predicate.hpp"
#include "beetree/nodes/reflexes/activate-reflex.hpp"
#include "beetree/nodes/select-if.hpp"
#include "beetree/services/api/bump-api.hpp"

namespace bte {

///
/// @ingroup reflex_nodes
///
/// IsBumping
/// =========
///
/// @see Predicate
///
/// Predicate node for querying if the robot is bumping
///
using IsBumping = Predicate<BumpAPI::is_bumping>;

///
/// @ingroup reflex_nodes
///
/// SelectIfBumping
/// ===============
///
/// @see SelectIf
///
/// Select node where the nodes' branch is looped if the robot is bumping
///
using SelectIfBumping = SelectIf<BumpAPI::is_bumping>;

///
/// @ingroup reflex_nodes
///
/// ActivateBumpReflex
/// ==================
///
/// @see ActivateReflexFnc
///
/// Activates the reflex based on the current state of the reflex.
///
using ActivateBumpReflex = ActivateReflexFnc<BumpAPI::get_reflex>;
}  // namespace bte