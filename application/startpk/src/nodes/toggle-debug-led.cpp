//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/nodes/toggle-debug-led.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/nodes/blackboard.hpp"
#include "beetree/services/i-debug-service.hpp"
#include "beetree/startpk/tokens.hpp"

namespace bte {

static Result loop(Context& c)
{
    auto debug_svc = blackboard::update<IDebugService>();
    if (debug_svc)
    {
        debug_svc->toggle_led();
    }

    return Status::Success;
}

Recipe make_toggle_debug_led() { return Builder(tokens::ToggleLEDNode, loop).finalize(); }
}  // namespace bte