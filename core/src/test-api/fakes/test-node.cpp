//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test-api/fakes/test-node.hpp"
#include <stdexcept>

namespace bte {
namespace test {

TestNode::TestNode(delegate::Build buildFnc)
    : m_node(buildFnc), m_context(m_node, m_exception, m_data, m_data_len)
{
    construct();
}
TestNode::TestNode(delegate::Build buildfnc, const Node& branch)
    : m_node(buildfnc, branch), m_context(m_node, m_exception, m_data, m_data_len)
{
    construct();
}
TestNode::~TestNode()
{
    teardown();
    if (m_recipe.destruct) m_recipe.destruct(m_context);
}

void TestNode::construct()
{
    m_recipe = m_node.build();

    m_data_len = m_recipe.data_len;
    if (m_data_len > MAX_DATA)
        throw std::runtime_error("Node's data size is too large for TestNode");
    m_context = Context(m_node, m_exception, m_data, m_data_len);

    if (m_recipe.construct) m_recipe.construct(m_context);
}

void TestNode::setup()
{
    if (m_recipe.setup) m_recipe.setup(context());
}

Context& TestNode::context() { return m_context; }

void TestNode::teardown()
{
    if (m_recipe.teardown) m_recipe.teardown(context());
}

void TestNode::destruct()
{
    if (m_recipe.destruct) m_recipe.destruct(m_context);
    m_data_len = 0;
}

}  // namespace test
}  // namespace bte