///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "beetree/engine/tree-extensions.hpp"

namespace bte {
bool TreeX::loop(Runner runner, Clock::milliseconds timeout)
{
    bool done = false;

    Clock::time_point start_ms = Clock::now();
    while (!done && Clock::elapsed(start_ms) < timeout)
    {
        EngineResult result = runner.step();
        done                = result.all_visited || result.is_running_leaf;
    }

    return done;
}

}  // namespace bte