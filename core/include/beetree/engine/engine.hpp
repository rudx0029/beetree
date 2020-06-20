///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------
#pragma once

#include "beetree/btos/optional.hpp"
#include "beetree/engine/connections.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/engine/exception.hpp"
#include "beetree/engine/i-fatal-listener.hpp"
#include "beetree/engine/i-node-listener.hpp"
#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"
#include "beetree/engine/stack.hpp"
#include "beetree/engine/status.hpp"
#include "beetree/engine/tree-result.hpp"
#include "beetree/engine/tree-stats.hpp"

namespace bte {

/// Controls execution of the behavior tree
class Engine
{
public:
    Engine() = default;

    // > CONFIGURE
    void configure(const Node* base_tree, uint8_t* stack, std::size_t len);
    void configure_trace(std::size_t id, bool enabled);
    void configure_connections(const Connections& c);
    void configure_fatal_listener(IFatalListener& listener);
    void configure_node_listener(INodeListener& listener);

    // > INTERFACE
    ///
    /// Cycles the engine looping the current node. If the current node
    /// indicates a Success or Failed status, the engine will navigate back
    /// to parent node. If the current node presents a new branch, the
    /// engine will navigate to the new branch.
    ///
    /// @return EngineResult
    ///
    EngineResult step();

    // > EVENT HANDLERS
    ///
    /// Handles receiving and processing an exception generated externally from
    /// this tree.
    ///
    /// @param ex the exception
    ///
    void on_exception(const Exception& ex);

private:
    class MetaNode
    {
    public:
        MetaNode() = default;
        MetaNode(const Element& el, const Recipe& r, const optional<Exception>& ex)
            : is_valid(true), recipe(r), context(*el.node, ex, el.data, el.len)
        {}

                      operator bool() const { return is_valid; }
        const Recipe* operator->() const { return &recipe; }
        Context&      operator*() { return context; }

    private:
        bool    is_valid = false;
        Recipe  recipe;
        Context context;
    };

    class DefaultFatalListener : public IFatalListener
    {
    public:
        void on_fatal_error() override;
    };

    // > MEMBERS
    void     handle_exception(const Exception&);
    void     init_node(MetaNode& info, const Node* parent);
    void     push(const Node& branch, const Node* trunk);
    MetaNode pop();

    // > STATE FIELDS
    optional<Exception> m_rcvd_exception{nullopt};
    optional<Exception> m_cur_exception{nullopt};
    Stack               m_stack;
    MetaNode            m_cur_node;
    TreeStats           m_tree_stats;
    //> CONFIG FIELDS
    std::size_t          m_trace_id      = 0;
    bool                 m_trace_enabled = false;
    const Node*          m_base_tree     = nullptr;
    Connections          m_connections;
    DefaultFatalListener m_default_fatal_listener;
    IFatalListener*      m_fatal_listener{&m_default_fatal_listener};
    INodeListener*       m_node_listener = nullptr;
};
}  // namespace bte