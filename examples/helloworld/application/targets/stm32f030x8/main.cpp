//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/btos/app-runner.hpp"
#include "beetree/units/units.hpp"
#include "helloworld-platform/helloworld-platform.hpp"
#include "helloworld/application.hpp"
#include "helloworld/install.hpp"

// The Platform
helloworld::Platform the_platform;
// The Application
helloworld::Application the_app{the_platform};

// Implement our system clock
namespace bte {
chrono::timepoint_ms chrono::now_ms() { return the_platform.clock().now_ms(); }
}  // namespace bte

int main(int argc, const char* argv[])
{
    // > 1. boot up and configure the hardware
    if (!helloworld::boot(the_platform)) return 1;  // platform boot error

    // > 2. initialize the application including behavior trees
    if (!helloworld::install(the_app)) return 2;  // application setup error

    // > 3. run the application
    bte::run(the_app, 10_ms);

    // > 4. shutdown the system
    helloworld::teardown(the_app);
    helloworld::teardown(the_platform);

    return 0;  // okay
}
