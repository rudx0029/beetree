//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include "beetree/nodes/action.hpp"
#include "beetree/nodes/predicate.hpp"
#include "beetree/nodes/select-if.hpp"
#include "beetree/services/api/reflexes-api.hpp"
#include "beetree/startpk/tokens.hpp"

namespace bte {

// > Action Node Types

///
/// @ingroup reflex_nodes
///
/// EnableReflexes
/// ==============
///
/// @see Action
///
/// Action node type for enabling reflex services
///
using EnableReflexes = Action<ReflexesAPI::enable, tokens::EnableReflexesNode>;

///
/// @ingroup reflex_nodes
///
/// DisableReflexes
/// ===============
///
/// @see Action
///
/// Action node type for disabling reflex services
///
using DisableReflexes = Action<ReflexesAPI::disable, tokens::DisableReflexesNode>;

// > Predicate Node Types

///
/// @ingroup reflex_nodes
///
/// AreReflexesEnabled
/// ==================
///
/// @see Predicate
///
/// Predicate node for querying if the reflex services are enabled
///
using AreReflexesEnabled = Predicate<ReflexesAPI::are_enabled, tokens::AreReflexesDisabledNode>;

///
/// @ingroup reflex_nodes
///
/// AreReflexesDisabled
/// ===================
///
/// @see Predicate
///
/// Predicate node for querying if the reflex services are disabled
///
using AreReflexesDisabled = Predicate<ReflexesAPI::are_disabled, tokens::AreReflexesDisabledNode>;

// > Select Nodes

///
/// @ingroup reflex_nodes
///
/// SelectIfReflexesEnabled
/// =======================
///
/// @see SelectIf
///
/// Select node where the nodes' branch is looped if the reflexes are enabled
///
using SelectIfReflexesEnabled = SelectIf<ReflexesAPI::are_enabled>;

///
/// @ingroup reflex_nodes
///
/// SelectIfReflexesDisabled
/// ========================
///
/// @see SelectIf
///
/// Select node where the nodes' branch is looped if the reflexes are disabled
///
using SelectIfReflexesDisabled = SelectIf<ReflexesAPI::are_disabled>;

}  // namespace bte