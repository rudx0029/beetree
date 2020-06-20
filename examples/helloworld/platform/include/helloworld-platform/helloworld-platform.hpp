///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/platform/i-discrete-input.hpp"
#include "beetree/platform/i-discrete-output.hpp"
#include "beetree/platform/i-serial-device.hpp"
#include "beetree/platform/i-system-clock.hpp"

namespace helloworld {
// forward declaration
class Platform;
bool boot(Platform&);
void teardown(Platform&);

class Platform
{
public:
    Platform() = default;

    // > Clock
    bte::ISystemClock& clock();

    // > Discrete Outputs
    bte::IDiscreteOutput& led();
    bte::IDiscreteOutput& debug();

    // > Discrete Inputs
    bte::IDiscreteInput& user_btn();

    // > Serial Devices
    bte::ISerialDevice& vcp();
};
}  // namespace helloworld