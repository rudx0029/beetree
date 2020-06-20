///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/engine/delegates.hpp"
#include "beetree/engine/result.hpp"
#include "beetree/trace/trace.hpp"

namespace bte {
// > forward declaration
struct Context;

///
/// A Recipe is a set of actions and events handlers for a given Node
/// Instance.
///
/// What does this really mean?
/// ---------------------------
/// When designing a behavior tree, the nodes do not know what to do. The
/// Recipe gives the nodes its instructions, what actions to perform and how
/// to handle events.
///
/// How does a node know what recipe to use?
/// ----------------------------------------
/// When declaring a node in a tree, it's mandatory to specify a `build()`
/// method that returns a Recipe. The build method is *what* generates the
/// recipe when the tree activates the node.
///
///
struct Recipe
{
    // > CONSTRUCTORS
    Recipe() = default;
    Recipe(TraceToken t, delegate::Loop l) : token(t), loop(l) {}

    /// the node's description, e.g. name
    TraceToken token;
    /// the length of data needed to store the node's state
    std::size_t data_len = 0;

    // > CONSTRUCT/DESTRUCT
    delegate::Construct construct = nullptr;
    delegate::Destruct  destruct  = nullptr;

    // > INTERFACE
    delegate::Setup    setup    = nullptr;
    delegate::Loop     loop     = nullptr;
    delegate::Teardown teardown = nullptr;

    // > EVENTS
    delegate::ExceptionEvt      on_exception       = nullptr;
    delegate::BranchCompleteEvt on_branch_complete = nullptr;
    delegate::TraceEvt          on_trace           = nullptr;

    // > VALIDITY
    bool is_valid() const { return loop != nullptr; }
         operator bool() const { return is_valid(); }
};
}  // namespace bte