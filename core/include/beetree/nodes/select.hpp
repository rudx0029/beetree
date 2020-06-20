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
/// @return makes the recipe for the `select` composite node.
///
Recipe make_select();

///
/// @ingroup nodes
///
/// Select Node
/// =====================
///
/// The Select composite node invokes each of its branches until one of its branches
/// returns `Result{Status::Success}. This provides an OR operation across its branches.
///
/// Usage
/// ---------
///
/// ```cpp
/// constexpr auto selectBranches = branches(node_a, node_b, node_c);
/// constexpr auto selectNode = Select{selectBranches};
/// ```
///
/// Returns
/// -------
///
/// |                                   |                                         |
/// |-----------------------------------|-----------------------------------------|
/// | `Result{Status::Success}`         | if one if its branches returns success. |
/// | `Result{Status::Fail}`            | if all branches fail.                   |
/// | `Result{Status::Running, branch}` | while any of its branches are invoked.  |
///
using Select = Composite<make_select>;

/**@}*/  // end node group
}  // namespace bte
