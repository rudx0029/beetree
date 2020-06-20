//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/models/data/reflex.hpp"

namespace bte {
struct ReflexesAPI
{
    using GetReflexFnc = Reflex (*)(void);

    static void enable();
    static void disable();

    static bool are_enabled();
    static bool are_disabled();

    static void activate(const Reflex&);
    static void deactivate_all();

    // activate reflex compile time variants
    template <const Reflex& REFLEX>
    static void activate()
    {
        activate(REFLEX);
    }
    template <GetReflexFnc FNC>
    static void activate()
    {
        activate(FNC());
    }
};
}  // namespace bte