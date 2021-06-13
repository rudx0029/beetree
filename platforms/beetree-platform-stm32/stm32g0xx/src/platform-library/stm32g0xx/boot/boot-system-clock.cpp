///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file System Clock boot for stm32g0xx devices
///-----------------------------------------------------------------------------
#include "beetree/platform/stm32g0xx/boot.hpp"
#include "beetree/platform/stm32g0xx/hal/stm32g0xx_ll_cortex.h"
#include "beetree/platform/stm32g0xx/hal/stm32g0xx_ll_rcc.h"
#include "beetree/platform/stm32g0xx/hal/stm32g0xx_ll_system.h"
#include "beetree/platform/stm32g0xx/hal/stm32g0xx_ll_utils.h"

namespace stm32g0xx
{
    void boot(SystemClock& clk)
    {
        /* SysTick_IRQn interrupt configuration */
        NVIC_SetPriority(SysTick_IRQn, 0);

        /* Start The Clock */
        SysTick_Config(SystemCoreClock / 1000);
    }
}  // namespace stm32g0xx