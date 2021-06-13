//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test-api/mocks/mock-node.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"

namespace bte {
namespace test {

struct Data
{
    IActions* actions = nullptr;
};

static std::map<int, IActions*> s_actions;

static Result loop(Context& c) { return c.get_data<Data>()->actions->loop(c); }

static void teardown(Context& c) { c.get_data<Data>()->actions->teardown(c); }
static void on_exception(const Exception& ex, Context& c)
{
    c.get_data<Data>()->actions->on_exception(ex, c);
}
static void on_branch_complete(Status s, Context& c)
{
    c.get_data<Data>()->actions->on_branch_complete(s, c);
}
static void on_trace(TraceStream& s, Context& c) { c.get_data<Data>()->actions->on_trace(s, c); }

namespace internal {
void install_actions(int ID, IActions& actions) { s_actions[ID] = &actions; }

void setup_mock_node(Context& c, int id)
{
    c.get_data<Data>()->actions = s_actions[id];
    c.get_data<Data>()->actions->setup(c);
}

Recipe mock_node_recipe(delegate::Setup s)
{
    return Builder(TraceToken(), loop)
        .add_data<Data>()
        .add_setup(s)
        .add_teardown(teardown)
        .add_handler(on_exception)
        .add_handler(on_branch_complete)
        .finalize();
}

}  // namespace internal
}  // namespace test
}  // namespace bte