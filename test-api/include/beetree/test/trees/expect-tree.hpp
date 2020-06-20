//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <vector>
#include "beetree/engine/node.hpp"

namespace bte {
namespace test {
///
/// The TreeWalker provides utility methods to walk a tree and verify the path
/// of the tree.
///
class Tree
{
public:
    ///
    /// During a test, call this to walk the tree and verify that the target
    /// node is reached. The method step the tree until the target is reached or
    /// until max iterations is reached.
    ///
    /// @param target The target node
    /// @param max_iterations Max iterations the method will step the tree
    ///
    ///
    static void EXPECT_NODE(const Node& target, const Node& root, uint32_t max_steps = 100);

    ///
    /// During a test, call this to walk the tree and verify that the expected
    /// path is reached. The method step the tree until the target is reached or
    /// until max iterations is reached.
    ///
    /// @param target The target node
    /// @param max_iterations Max iterations the method will step the tree
    ///
    ///
    static void EXPECT_PATH(std::vector<const Node*> expected_path,
                            const Node&              root,
                            uint32_t                 max_steps = 100);
};

}  // namespace test
}  // namespace bte