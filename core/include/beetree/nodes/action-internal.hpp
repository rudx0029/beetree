//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/context.hpp"
#include "beetree/engine/recipe.hpp"

namespace bte {

template <delegate::Action A>
Result loop_action(Context& c)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waddress"
    if (A != nullptr) A();
#pragma GCC diagnostic pop
    return Status::Success;
}

template <delegate::Action A, const TraceToken& T>
Recipe make_action()
{
    return {T, loop_action<A>};
}

}  // namespace bte