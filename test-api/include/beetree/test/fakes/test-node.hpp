//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/context.hpp"
#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"

namespace bte {
namespace test {
class TestNode
{
public:
    // > Aliases
    using delegate = bte::delegate;

    // > Constructors
    TestNode() = default;
    TestNode(delegate::Build buildFnc);
    TestNode(delegate::Build buildfnc, const bte::Node& branch);
    template <std::size_t N>
    TestNode(delegate::Build buildfnc, const bte::Branches<N>& br) : m_node(buildfnc, br)
    {
        construct();
    }

    // > Properties
    const bte::Node&   node() const { return m_node; }
    bte::Context&      context();
    const bte::Recipe& recipe() const { return m_recipe; }

    // > Actions
    void construct();  /// < to be called on test setup
    void setup();      /// < to be called on test setup
    void teardown();   /// < to be called on test teardown
    void destruct();   /// < to be called on test teardown

    // > Operators
    /// gives direct acces to the nodes actions, e.g. setup, loop,
    /// on_branch_complete, teardown
    const bte::Recipe* operator->() const { return &m_recipe; }

    // Leaf/Branch no-op build function
    static bte::Recipe no_op() { return bte::Recipe(); }

    // > Destructor
    ~TestNode();

    // > Deleted Members
    TestNode(const TestNode&) = delete;
    TestNode& operator=(const TestNode&) = delete;

private:
    static constexpr int          MAX_DATA{512};
    uint8_t                       m_data[MAX_DATA];
    int                           m_data_len = 0;
    bte::Node                     m_node;    ///< the node under test
    bte::Recipe                   m_recipe;  ///<
    bte::Context                  m_context;
    bte::optional<bte::Exception> m_exception{bte::nullopt};
};
}  // namespace test
}  // namespace bte