//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/btos/app-runner.hpp"

namespace bte {
static void idle(IApplication& app, Clock::time_point idleEnd, void (*yield)())
{
    bool first_time = true;
    while (Clock::now() < idleEnd)
    {
        app.on_idle(first_time);
        first_time = false;
        if (yield)
        {
            yield();
        }
    }
}

void run(IApplication& app, Clock::milliseconds scan_interval, void (*yield)())
{
    constexpr bool running = true;
    // run the application
    while (running)
    {
        Clock::time_point startTp = Clock::now();
        Clock::time_point endTp   = startTp + scan_interval;

        app.sense();

        app.process();

        app.actuate();

        Clock::milliseconds dur = Clock::elapsed(startTp);

        if (dur <= scan_interval)
        {
            idle(app, endTp, yield);
        }
        else
        {
            app.on_overrun(dur);
            idle(app, endTp + scan_interval, yield);  // todo: need to generalize
                                                      // the overrun for all cases.
        }
    }
}  // namespace ctos
}  // namespace bte