//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/platform/stm32f0xx/hal/stm32f0xx_ll_system.h"
#include "beetree/platform/stm32f0xx/hal/stm32f0xx_ll_gpio.h"
#include "beetree/platform/stm32f0xx/hal/stm32f0xx_ll_exti.h"
#include "beetree/platform/stm32f0xx/boot.hpp"
#include "beetree/platform/stm32f0xx/helpers.hpp"
#include "beetree/platform/stm32f0xx/counter.hpp"


namespace stm32f0xx {

//
// This file supports the line interrupt hardware.
// There are two modalities that want interrupts: 
// - encoder ticks
// - bumpers
// So this file is generic to exti, not application of exti
//
namespace exti_line11
{
void boot_exti_line11(CounterOnPc11& counter, bte::ISystemClock& clock)
{
    counter.set_clock(clock);

    LL_EXTI_InitTypeDef EXTI_InitStruct;
    
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE11);
    
    EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_11;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
    LL_EXTI_Init(&EXTI_InitStruct);

    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_11, LL_GPIO_MODE_INPUT);
}
}

namespace exti_line12
{
void boot_exti_line12(CounterOnPc12& counter, bte::ISystemClock& clock)
{
    counter.set_clock(clock);

    LL_EXTI_InitTypeDef EXTI_InitStruct;

    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE12);

    EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_12;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
    LL_EXTI_Init(&EXTI_InitStruct);

    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_12, LL_GPIO_MODE_INPUT); 
}
}

namespace exti_line0
{
void boot_exti_line0(CounterOnPc0& counter, bte::ISystemClock& clock)
{
    counter.set_clock(clock);

    LL_EXTI_InitTypeDef EXTI_InitStruct;
    
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE0);
    
    EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_0;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
    LL_EXTI_Init(&EXTI_InitStruct);

    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_INPUT);
}
}

namespace exti_line1
{
void boot_exti_line1(CounterOnPc1& counter, bte::ISystemClock& clock)
{
    counter.set_clock(clock);

    LL_EXTI_InitTypeDef EXTI_InitStruct;

    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE1);

    EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_1;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
    LL_EXTI_Init(&EXTI_InitStruct);

    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_1, LL_GPIO_MODE_INPUT);
}
}
}  // namespace stm32f0xx