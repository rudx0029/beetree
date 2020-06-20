///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------
#pragma once

#include "beetree/btos/clock.hpp"
#include "beetree/engine/runner.hpp"
#include "beetree/engine/tree.hpp"

namespace bte {
/// Extension methods for the behavior tree engine.
struct TreeX
{
    ///
    /// Steps the tree multiple times until one of the following
    /// conditions is reached:
    ///  - an active, running leaf is reached
    ///  - all nodes in the tree have been visited
    ///  - a timeout occurs.
    ///
    /// @param runner the tree runner
    /// @param timeout max duration of the operation
    /// @return true when an active, running leaf is reach or all nodes have
    /// been visited
    /// @return false when a timeout occurs
    ///
    static bool loop(Runner runner, Clock::ms timeout);

    ///
    /// Steps the tree multiple times until one of the following
    /// conditions is reached:
    ///  - an active, running leaf is reached
    ///  - all nodes in the tree have been visited
    ///  - a timeout occurs.
    ///
    /// @note
    /// this is a convenience method for @see loop(Runner,ctos::Clock::ms)
    ///
    /// @tparam N the tree's stack size in bytes
    /// @param tree the tree
    /// @param timeout max duration of the operation
    /// @return true when an active, running leaf is reach or all nodes have
    /// been visited
    /// @return false when a timeout occurs
    ///
    template <std::size_t N>
    static bool loop(Tree<N>& tree, Clock::ms timeout)
    {
        return loop(tree.runner(), timeout);
    }
};
}  // namespace bte