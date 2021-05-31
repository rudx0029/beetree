///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------
#include "beetree/engine/builder.hpp"
#include "beetree/core/tokens.hpp"

namespace bte {

Builder::Builder(TraceToken token, delegate::Loop loop) : m_recipe(token, loop) {}

Builder& Builder::add_setup(delegate::Setup setup)
{
    m_recipe.setup = setup;
    return *this;
}

Builder& Builder::add_teardown(delegate::Teardown teardown)
{
    m_recipe.teardown = teardown;
    return *this;
}

Builder& Builder::add_handler(delegate::ExceptionEvt on_exception)
{
    m_recipe.on_exception = on_exception;
    return *this;
}

Builder& Builder::add_handler(delegate::BranchCompleteEvt on_branch_complete)
{
    m_recipe.on_branch_complete = on_branch_complete;
    return *this;
}

Builder& Builder::add_handler(delegate::TraceEvt on_trace)
{
    m_recipe.on_trace = on_trace;
    return *this;
}

Recipe Builder::finalize() const { return m_recipe; }

void Builder::fail_invalid_state() { fail(tokens::InvalidState); }
}  // namespace bte