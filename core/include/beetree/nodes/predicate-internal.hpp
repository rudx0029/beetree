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

template <delegate::Predicate P>
Result loop_predicate(Context& c)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waddress"
    return ((P != nullptr) && P()) ? Status::Success : Status::Fail;
#pragma GCC diagnostic pop
}

template <delegate::Predicate P, const TraceToken& T>
Recipe make_predicate()
{
    return {T, loop_predicate<P>};
}

}  // namespace bte