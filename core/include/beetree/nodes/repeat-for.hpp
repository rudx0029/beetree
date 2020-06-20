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

/// @ingroup make
///
/// Setup method for the `RepeatFor` decorator
///
/// @param c        Tree context.
/// @param num_reps The number of times the `RepeatFor` decorator should execute its branch
/// @return makes the recipe for the `RepeatFor` decorator node.
///
void setup_repeat_for(Context& c, std::size_t num_reps);
///
/// @ingroup make
/// @return the recipe for the `RepeatFor` decorator node.
///
Recipe make_repeat_for(delegate::Setup);

///
/// @ingroup make
///
/// Template argument wrapper for `setup_repeat_for`.
///
/// @tparam NumReps The number of times the `RepeatFor` decorator should execute its branch
/// @param c Tree Context
///
template <std::size_t NumReps>
void setup_repeat_for(Context& c)
{
    setup_repeat_for(c, NumReps);
}

///
/// @ingroup make
///
/// Template argument wrapper for `make_repeat_for`
/// @tparam NumRepetitions The number of times the `RepeatFor` decorator should execute its branch
/// @return the recipe for the `RepeatFor` decorator node.
///
template <std::size_t NumRepetitions>
Recipe make_repeat_for()
{
    return make_repeat_for(setup_repeat_for<NumRepetitions>);
}

///
/// @ingroup nodes
///
/// RepeatFor Node
/// ==============
///
/// The RepeatFor decorator will repeatedly visit and invoke it's branch
/// NumRepetitions before returning. If the branch fails at any time, then the
/// repeat for will immediately return a fail result without completing the
/// repetitions.
///
///
///
/// Usage
/// -----
///
/// ```cpp
/// static int counter = 0;
/// inline static inc_count(){ counter++; }
///
/// constexpr Action<inc_count> action;
///
/// constexpr auto repeatFor20Times = RepeatFor<20>{action};
/// // counter will be 20 when repeatFor20Times returns
/// ```
///
/// Parameters
/// ----------
///
/// |                |                                                            |
/// |----------------|------------------------------------------------------------|
/// | NumRepetitions | the number of repetitions to invoke the child branch after |
///
/// Returns
/// -------
///
/// |                                   |                                                         |
/// |-----------------------------------|---------------------------------------------------------|
/// | `Result{Status::Success}`         | if the branch completes successfully for NumRepetitions |
/// | `Result{Status::Success}`         | if NumRepetitions is 0                                  |
/// | `Result{Status::Running, branch}` | while the branch repeatedlyreturns fail.                |
/// | `Result{Status::Fail}`            | if the branch fails at anytime                          |
/// |`Result{Status::Fail}`             | if the branch is invalid                                |
///
template <std::size_t NumRepetitions>
using RepeatFor = Decorator<make_repeat_for<NumRepetitions>>;
}  // namespace bte