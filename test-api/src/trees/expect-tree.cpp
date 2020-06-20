//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/test/trees/expect-tree.hpp"
#include "beetree/engine/tree.hpp"
#include "beetree/test/gtest-ns.hpp"

namespace bte {
namespace test {

class Recorder : public INodeListener
{
public:
    void on_node_active(const Node& node) override { path.emplace_back(&node); }

    std::vector<const Node*> path;
};

struct Walker
{
    bte::Tree<512> tree;
    Recorder       recorder;

    Walker(const Node& root)
    {
        tree.configure_root(root);
        tree.configure_node_listener(recorder);
    }
};

void Tree::EXPECT_NODE(const Node& target, const Node& root, uint32_t max_steps)
{
    Walker walker(root);

    bool reached_node = false;
    for (uint32_t i = 0; i < max_steps; i++)
    {
        walker.tree.runner().step();
        if (walker.recorder.path.back() == &target)
        {
            reached_node = true;
            break;
        }
    }

    EXPECT_TRUE(reached_node);
}

void Tree::EXPECT_PATH(std::vector<const Node*> path, const Node& root, uint32_t max_steps)
{
    Walker walker(root);

    bool path_found = false;
    for (uint32_t step = 0; step < max_steps; step++)
    {
        walker.tree.runner().step();

        if (walker.recorder.path.size() >= path.size() && !path.empty())
        {
            path_found =
                std::equal(path.begin(), path.end(), walker.recorder.path.end() - path.size());
        }

        if (path_found) break;
    }

    EXPECT_TRUE(path_found);
}

}  // namespace test
}  // namespace bte