//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/engine.hpp"
#include "beetree/engine/notifier.hpp"
#include "beetree/engine/runner.hpp"

namespace bte {
///
/// The tree is the one stop shop for allocating a tree stack, configuring
/// the engine, e.g. setting the tree's root node, connections, etc., and
/// accessing the trees notification system (Notifier) and runtime system
/// (Runner)
///
/// @tparam STACK_SIZE The size in bytes alloted to the trees stack
///
template <std::size_t STACK_SIZE>
class Tree
{
public:
    Tree() = default;
    Tree(const Node& root) { configure_root(root); }

    ///
    /// Configures the tree's root node.
    ///
    /// @note
    /// This is mandatory to call when installing the application
    ///
    /// @param root the tree's root node of its behavior tree
    ///
    void configure_root(const Node& root) { m_engine.configure(&root, m_stack, m_stack_size); }

    ///
    /// Configures the trees connections to ports
    ///
    /// @note
    /// This method is optional during application installation
    ///
    /// @note
    /// Use this method if your connections are defined as an array
    /// and not in the object form.
    ///
    /// @tparam N the number of connections, implicitly declared
    /// @param c an array of connections with size N
    ///
    template <std::size_t N>
    void configure_connections(const ConnectionArray<N>& c)
    {
        m_engine.configure_connections(c);
    }

    ///
    /// Configures the trees connections to ports
    ///
    /// @note
    /// This method is optional during application installation
    ///
    /// @note
    /// Use this method if your connections are defined as the object.
    ///
    /// @param c the connections
    ///
    void configure_connections(const Connections& c) { m_engine.configure_connections(c); }

    ///
    /// Enable or disable tracing of nodes while the tree is traversed.
    ///
    /// @param id The tree's id which **must** be unique if there are
    /// multiple trees running concurrently. Defaults to 0.
    /// @param enabled true to enable tracing for tree. Defaults to false.
    ///
    void configure_trace(std::size_t id, bool enabled) { m_engine.configure_trace(id, enabled); }
    ///
    /// Sets the fatal listener for the tree. (optional)
    ///
    /// When the tree's engine detects a fatal error, the fatal listener is
    /// invoked which is intended to handle the fatal error, i.e. assert
    ///
    /// @param listener The fatal listener
    ///
    void configure_fatal_listener(IFatalListener& listener)
    {
        m_engine.configure_fatal_listener(listener);
    }
    ///
    /// Sets the node listener for the tree. (optional)
    ///
    /// When the tree's engine traverses to the next node, the node listener is
    /// invoked with a reference to the next node.
    ///
    /// @param listener The node listener
    ///
    void configure_node_listener(INodeListener& listener)
    {
        m_engine.configure_node_listener(listener);
    }
    ///
    /// Accessor to the trees notification system
    ///
    /// @return a tree's notifier for raising exceptions or the
    /// like
    ///
    Notifier notifier() { return {m_engine}; }
    ///
    /// Accessor to the trees runtime system
    ///
    /// @return a runner to step through the tree.
    ///
    Runner runner() { return {m_engine}; }

private:
    std::size_t m_stack_size = STACK_SIZE;
    uint8_t     m_stack[STACK_SIZE];
    Engine      m_engine;
};
}  // namespace bte