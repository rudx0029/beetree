//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/btos/clock.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"

namespace bte {

// > Interface
void   setup_idle(Context& c, const Clock::ms& duration);
Recipe make_idle(delegate::Setup s);

template <const Clock::ms& Duration>
void setup_idle(Context& c)
{
    setup_idle(c, Duration);
}

template <const Clock::ms& Duration>
Recipe make_idle()
{
    return make_idle(setup_idle<Duration>);
}
}  // namespace bte