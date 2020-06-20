//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/btos/assert.hpp"

namespace bte {

static Assert::IHandler* s_assert_handler = nullptr;

void Assert::install(Assert::IHandler& handler) { s_assert_handler = &handler; }

void fail(const TraceToken& token)
{
    if (s_assert_handler)
    {
        s_assert_handler->on_fail(token);
    }
    else
    {
        trace::fatal(token);
    }

    while (true)
    {
        // do nothing forever
    }
}

}  // namespace bte