//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include "beetree/engine/node.hpp"

namespace bte {
///
/// The BranchReader is an iterator for a node's branch. Using a valid
/// context, each branch can be iterated from the begining to the end.
///
/// > A valid context has a node and the node has one or more branches.
///
/// When the tree activates the context's node, several actions of the
/// node's Recipe, e.g. `setup`, `loop`, `on_branch_complete` are executed.
/// Use the BranchReader to access and iterate through a node's branches.
///
struct BranchReader final
{
    using const_iterator = Node::const_iterator;

    ///
    /// @return the number of branches node has
    /// @return 0 if the context is not valid
    ///
    static std::size_t size(const Node& c);

    ///
    /// @return a constant iterator to the node's first branch
    /// @return nullptr if the context is not valid.
    ///
    static Node::const_iterator begin(const Node& c);

    ///
    /// @return a constant iterator to marking the end of the node's
    /// branches.
    /// @return nullptr if the context is not valid.
    ///
    /// @note The iterator return does not point to a branch but marks the
    /// end of the collection of branches.
    ///
    static Node::const_iterator end(const Node& c);

private:
    const Node* m_node = nullptr;
};
}  // namespace bte