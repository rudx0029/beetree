///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file Implementation of the Beetree Engine.
///-----------------------------------------------------------------------------

#include "beetree/engine/engine.hpp"
#include "beetree/btos/assert.hpp"
#include "beetree/btos/clock.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/engine/port.hpp"
#include "beetree/engine/result.hpp"
#include "beetree/engine/try-catch.hpp"

// internal library
#include "helpers.hpp"
#include "port-internal.hpp"
#include "try-catch-internal.hpp"

namespace bte {
namespace internal {
static void trace_title()
{
    static Clock::time_point      s_start;
    constexpr Clock::milliseconds FIVE_MIN{1000 * 60 * 5};

    if (Clock::elapsed(s_start) > FIVE_MIN)
    {
        trace::info(tokens::Title) << "Beetree!";
        trace::info(tokens::Title) << "Robot Framework";
        trace::info(tokens::Copyright) << "Copyright 2020";
        trace::info(tokens::Copyright) << "BeeTree";
        trace::info(tokens::Copyright) << "Authors";

        s_start = Clock::now();
    }
}
}  // namespace internal

void Engine::DefaultFatalListener::on_fatal_error() { fail(tokens::FatalError); }

///////////////////////////////////
/// > CONFIGURATION
///////////////////////////////////

void Engine::configure(const Node* idle_tree, uint8_t* stack, std::size_t len)
{
    m_base_tree = idle_tree;
    m_stack.configure(stack, len);
    m_cur_node = MetaNode{};
}

void Engine::configure_trace(std::size_t id, bool enabled)
{
    m_trace_id      = id;
    m_trace_enabled = enabled;
}
void Engine::configure_connections(const Connections& c) { m_connections = c; }

void Engine::configure_fatal_listener(IFatalListener& listener) { m_fatal_listener = &listener; }

void Engine::configure_node_listener(INodeListener& listener) { m_node_listener = &listener; }

///////////////////////////////////
/// > EXCEPTION HANDLING
///////////////////////////////////

void Engine::on_exception(const Exception& ex)
{
    if (!m_rcvd_exception)
    {
        m_rcvd_exception = ex;
    }
    else
    {
        trace::warn(tokens::ExceptionIgnored) << static_cast<uint32_t>(ex.type());
    }
}

void Engine::handle_exception(const Exception& ex)
{
    m_cur_exception = ex;
    while (!m_stack.empty())
    {
        // - absolutely ensure node validity
        // - this is a bug otherwise.
        if (!m_cur_node)
        {
            m_fatal_listener->on_fatal_error();
        }

        // inform the current node an exception occurred
        trace::error(tokens::ExceptionStack)
            << static_cast<uint32_t>(ex.type()) << m_cur_node->token;
        // TODO: add meta node address for
        // visual graph support

        // Signal the exception
        if (m_cur_node->on_exception)
        {
            m_cur_node->on_exception(ex, *m_cur_node);
        }
        // if the node is a try_catch and the try node is active then break
        // from the loop and let the tree run
        if (internal::is_try_catch_node_strict((*m_cur_node).get_node(), ex.type()))
        {
            auto state = (*m_cur_node).get_data<internal::TryCatchData>();
            if (internal::is_try_active(state, *m_cur_node)) break;
        }

        m_cur_node = pop();
    }

    // signal unhandled exception and push the root node
    if (m_stack.empty())
    {
        trace::error(tokens::UnhandledException) << static_cast<uint32_t>(ex.type()) << ex.arg();
        // release the current exception before push,
        // removing it from the active context
        m_cur_exception.reset();
        push(*m_base_tree, nullptr);
    }
}

///////////////////////////////////
/// > RUN OPERATIONS
///////////////////////////////////

EngineResult Engine::step()
{
    Status status = Status::Running;  // always return running until the
                                      // tree has been navigated
    bool is_running_leaf = false;

    // push the default/idle tree on to the stack if nothing is active
    if (m_stack.empty())
    {
        internal::trace_title();
        push(*m_base_tree, nullptr);
    }

    // handle any exceptions
    if (m_rcvd_exception)
    {
        optional<Exception> ex{nullopt};
        bte::swap(m_rcvd_exception, ex);
        handle_exception(ex.value());
    }

    // todo: check for invalid branch ?? via m_cur_branch.storage.is_valid

    // Execute the current node and process the result
    Result result = m_cur_node->loop(*m_cur_node);
    switch (result.status)
    {
        case Status::Running:
            if (result.branch != nullptr)
            {
                push(*result.branch, &(*m_cur_node).get_node());
                // note: m_details has been modified after a call to push
            }
            else
            {
                is_running_leaf = true;
            }
            break;
        case Status::Success:
        case Status::Fail:
            // the branch is done so pop it.
            m_cur_node = pop();

            // If th stack is not empty,
            // then the storage is valid
            if (m_cur_node)
            {
                // notify the decorator/composite of the branch's status
                if (m_cur_node->on_branch_complete)
                {
                    m_cur_node->on_branch_complete(result.status, *m_cur_node);
                }

                if (internal::is_try_catch_node((*m_cur_node).get_node()))
                {
                    auto state = (*m_cur_node).get_data<internal::TryCatchData>();
                    if (internal::is_catch_active(state, *m_cur_node))
                    {
                        // if the catch tree returns Fail, then rethrow
                        // the exception
                        if (Status::Fail == result.status)
                        {
                            if (m_cur_exception)
                            {
                                on_exception(m_cur_exception.value());
                            }
                            else
                            {
                                // TODO: Log a warning
                            }
                        }
                        // clear the current exception
                        // when the final catch branch
                        // completes    
                        m_cur_exception.reset();
                    }
                }
            }
            else
            {
                // This means we have iterated through the whole tree.
                // - return the final status of the tree.
                status = result.status;
            }
            break;
    }

    return EngineResult{status, is_running_leaf, m_stack.empty()};
}

///////////////////////////////////
/// > STACK OPERATIONS
///////////////////////////////////

Engine::MetaNode Engine::pop()
{
    MetaNode next_node;

    // first tear down the current node
    if (m_cur_node->teardown) m_cur_node->teardown(*m_cur_node);

    // destruct any of the node's user data
    if (m_cur_node->destruct) m_cur_node->destruct(*m_cur_node);

    // release the memory from storage
    m_stack.pop();

    // now setup up the current node as the top of the stack
    // note: if el is invalid, then the stack is empty
    Element el = m_stack.top();

    // if the element is valid, then populate the details with the recipe,
    // otw the details will stay invalidated via the default constructor
    if (el)
    {
        next_node = MetaNode{el, el.node->build(), m_cur_exception};

        if (m_node_listener)
        {
            m_node_listener->on_node_active(*el.node);
        }
    }

    return next_node;
}

void Engine::push(const Node& branch, const Node* trunk)
{
    if (branch.build != nullptr)
    {
        Recipe recipe = branch.build();
        if (m_stack.push(branch, recipe.data_len))
        {
            // set the current node from the top of the stack
            m_cur_node = MetaNode{m_stack.top(), recipe, m_cur_exception};

            // construct any of the node's user data
            if (m_cur_node->construct) m_cur_node->construct(*m_cur_node);

            // if the node is a port, set it up directly
            if (branch.build == port_optional || branch.build == port_mandatory)
            {
                // setup the port internally
                internal::port_setup(*m_cur_node,
                                     helpers::find_connection(branch, m_connections),
                                     branch.build == port_mandatory /*is mandator*/);
            }
            // set up the node, if specified
            else if (m_cur_node->setup)
            {
                m_cur_node->setup(*m_cur_node);
            }

            // finish initializing the node
            init_node(m_cur_node, trunk);
        }
        else
        {
            m_fatal_listener->on_fatal_error();
        }
    }
    else
    {
        m_fatal_listener->on_fatal_error();
    }
}

void Engine::init_node(Engine::MetaNode& cur_node, const Node* trunk)
{
    if (m_trace_enabled)
    {
        // upon initialization, trace the node
        TraceStream s = trace::channels::nodes(cur_node->token);
        // uniquely package the node and trunk as the first
        // argument
        s << helpers::package_for_trace(m_trace_id, (*cur_node).get_node(), trunk);

        // add any final arguments from the node
        if (cur_node->on_trace)
        {
            cur_node->on_trace(s, *m_cur_node);
        }
    }

    if (m_node_listener)
    {
        m_node_listener->on_node_active((*cur_node).get_node());
    }
}

}  // namespace bte