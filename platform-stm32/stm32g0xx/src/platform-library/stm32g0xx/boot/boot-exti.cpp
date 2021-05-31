//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "platform-library/stm32g0xx/hal/stm32g0xx_ll_system.h"
#include "platform-library/stm32g0xx/hal/stm32g0xx_ll_gpio.h"
#include "platform-library/stm32g0xx/hal/stm32g0xx_ll_exti.h"
#include "platform-library/stm32g0xx/boot.hpp"
#include "platform-library/stm32g0xx/helpers.hpp"
#include "platform-library/stm32g0xx/counter.hpp"


namespace stm32g0xx {

//
// This file supports the line interrupt hardware.
// There are two modalities that want interrupts: 
// - encoder ticks
// - bumpers
// So this file is generic to exti, not application of exti
//

namespace exti_line1
{
void boot_exti_line1(CounterOnPa1& counter, bte::ISystemClock& clock)
{
    counter.set_clock(clock);

    LL_EXTI_InitTypeDef EXTI_InitStruct;
    
    LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA, LL_EXTI_CONFIG_LINE1);
    
    EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_1;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
    LL_EXTI_Init(&EXTI_InitStruct);
    
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_1, LL_GPIO_PULL_UP);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_1, LL_GPIO_MODE_INPUT);
}
}

namespace exti_line2
{
void boot_exti_line2(CounterOnPb2& counter, bte::ISystemClock& clock)
{
    counter.set_clock(clock);

    LL_EXTI_InitTypeDef EXTI_InitStruct;

    LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTB, LL_EXTI_CONFIG_LINE2);

    EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_2;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
    LL_EXTI_Init(&EXTI_InitStruct);
    
    LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_2, LL_GPIO_PULL_UP);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_2, LL_GPIO_MODE_INPUT);
}
}
}  // namespace stm32g0xx