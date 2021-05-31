///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "beetree/engine/branch-reader.hpp"
#include "beetree/engine/context.hpp"

namespace bte {
using BranchReader   = BranchReader;
using const_iterator = BranchReader::const_iterator;

enum class NodeType
{
    Invalid,
    Composite,
    Decorator
};

static NodeType get_type(const Node& node)
{
    NodeType type = NodeType::Invalid;

    // prioritize on composite over decorator
    if (node.branches && node.num_branches > 0)
        type = NodeType::Composite;
    else if (node.branch)
        type = NodeType::Decorator;

    return type;
}

std::size_t BranchReader::size(const Node& node)
{
    NodeType t = get_type(node);
    switch (t)
    {
        case NodeType::Composite:
            return node.num_branches;
        case NodeType::Decorator:
            return 1;
        default:
            return 0;
    }
}

const_iterator BranchReader::begin(const Node& node)
{
    NodeType t = get_type(node);
    switch (t)
    {
        case NodeType::Composite:
            return &node.branches[0];
        case NodeType::Decorator:
            return &node.branch;
        default:
            return nullptr;
    }
}

const_iterator BranchReader::end(const Node& node)
{
    NodeType t = get_type(node);
    switch (t)
    {
        case NodeType::Composite:
            return &node.branches[node.num_branches];
        case NodeType::Decorator:
            // represent the single branch as an array
            // and say the end is the next element
            return &(&node.branch)[1];
        default:
            return nullptr;
    }
}
}  // namespace bte