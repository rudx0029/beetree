///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/btos/assert.hpp"
#include "beetree/btos/construct-memory.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/engine/exception.hpp"
#include "beetree/engine/recipe.hpp"

namespace bte {

// > Contents:
// >  1. Builder - the primitive builder for a node's recipe
// >  2. StateBuilder - automates management of a nodes data  while building the
// >  node's recipe.

///
/// A builder interface for creating node recipes
///
/// Usage:
/// @code
/// Recipe my_node()
/// {
///     return Builder(tokens::MyNode, loop)
///             .add_data<MyState>
///             .add_setup(setup)
///             .add_handler(on_exception)
///             .finalize();
/// }
/// @endcode
///
class Builder
{
public:
    // > Mandatory Methods
    /// Constructor - mandatory args for the recipe
    Builder(TraceToken token, delegate::Loop loop);

    /// Finalize and return the recipe. This should be called after all
    /// options and data have been specified
    Recipe finalize() const;

    // > Optional Setup and Teardown

    /// Optionally add a setup method with out any state data
    Builder& add_setup(delegate::Setup setup);

    /// Optionally add a teardown method with out any state data
    Builder& add_teardown(delegate::Teardown teardown);

    // > Optional Event Handlers
    /// add exception handler
    Builder& add_handler(delegate::ExceptionEvt);
    /// add branch complete handler
    Builder& add_handler(delegate::BranchCompleteEvt);
    /// add trace handler for providing extending tracing information
    Builder& add_handler(delegate::TraceEvt);

    // > Optionally Add State With Setup and Teardown

    /// Add state data
    template <class TState>
    Builder& add_data()
    {
        m_recipe.construct = construct<TState>;
        m_recipe.destruct  = destruct<TState>;
        m_recipe.data_len  = sizeof(TState);
        return *this;
    }

private:
    Recipe m_recipe;

    template <class T>
    static void construct(Context& c)
    {
        if (memory::is_valid<T>(c.m_data, c.m_len))
        {
            memory::construct<T>(c.m_data);
        }
        else
        {
            fail_invalid_state();
        }
    }

    template <class T>
    static void destruct(Context& c)
    {
        memory::destruct<T>(c.m_data);
    }

    static void fail_invalid_state();
};
}  // namespace bte