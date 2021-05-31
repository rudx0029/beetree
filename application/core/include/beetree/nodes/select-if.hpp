//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"

namespace bte {

///
/// @ingroup make
///
/// Loop method for SelectIf node
///
/// @param c the tree's context
/// @param pred predicate function pointer
/// @return Result
///
Result loop_select_if(Context& c, delegate::Predicate pred);

///
/// @ingroup make
///
/// Make function for SelectIf node.
///
/// @param loop a reference to loop_select_if<P>()
/// @return Recipe
///
Recipe make_select_if(delegate::Loop loop);

/// @ingroup make
///
/// Template parameter wrapper for SelectIf's loop
/// @tparam P predicate function pointer
/// @param c the tree's context
/// @return Result
///
template <delegate::Predicate P>
Result loop_select_if(Context& c)
{
    return loop_select_if(c, P);
}

/// @ingroup make
///
/// Template parameter wrapper for SelectIfs make function
///
/// @tparam P predicate function pointer
/// @return SelectIf's build recipe
///
template <delegate::Predicate P>
Recipe make_select_if()
{
    return make_select_if(loop_select_if<P>);
}

///
/// @ingroup nodes
///
///
/// SelectIf Node
/// =======================
///
/// The select_if decorator will return its branch if the predicate
/// returns true. Otherwise, the decorator will return a status of FAIL
///
/// Parameters
/// ----------
///
/// |            |                                                                 |
/// |------------|-----------------------------------------------------------------|
/// | P          | predicate returning true to select the branch and false not to. |
///
/// Returns
/// -------
///
/// |                                   |                                              |
/// |-----------------------------------|----------------------------------------------|
/// | `Result{Status::Success}`         | when the selected child branch is successful |
/// | `Result{Status::Fail }`           | when the selected child branch fails         |
/// | `Result{Status::Running, branch}` | when a child branch is selected and invoked  |
/// | `Result{Status::Fail}`            | when the predicate returns false             |
/// | `Result{Status::Fail}`            | when the predicate or branch is invalid      |
///
/// Usage
/// -----
///
/// The following creates a SelectIf node to null odometry if the robot is
/// stopped.
/// ```
/// inline bool is_stopped()
///     { return blackboard::get_assert<IMotionService>().model().is_stopped; }
///
/// constexpr NullOdometry nullOdometry;
/// constexpr auto selectNullOdometry = SelectIf<is_stopped>{nullOdometry};
/// ```
template <delegate::Predicate P>
using SelectIf = Decorator<make_select_if<P>>;
}  // namespace bte