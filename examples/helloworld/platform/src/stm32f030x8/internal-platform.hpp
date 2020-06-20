///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------
#pragma once

#include "helloworld-platform/helloworld-platform.hpp"

#include "platform-library/stm32f0xx/discrete-input.hpp"
#include "platform-library/stm32f0xx/discrete-output.hpp"
#include "platform-library/stm32f0xx/serial-device-uart-dma.hpp"
#include "platform-library/stm32f0xx/system-clock.hpp"

namespace helloworld {
class InternalPlatform
{
public:
    static InternalPlatform& instance();

    // > MEMBERS
    stm32f0xx::SystemClock           clock;
    stm32f0xx::DiscreteOutput        led;
    stm32f0xx::DiscreteOutput        debug;
    stm32f0xx::DiscreteInputInv      user_btn;
    stm32f0xx::SerialDevice_UART_DMA vcp;

private:
    InternalPlatform() = default;
};
}  // namespace helloworld