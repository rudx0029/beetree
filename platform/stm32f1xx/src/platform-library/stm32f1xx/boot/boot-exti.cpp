//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "../hal/stm32f1xx_ll_exti.h"
#include "../hal/stm32f1xx_ll_gpio.h"
#include "platform-library/stm32f1xx/boot.hpp"
#include "platform-library/stm32f1xx/counter.hpp"
#include "platform-library/stm32f1xx/helpers.hpp"

namespace stm32f1xx {

//
// This file supports the line interrupt hardware.
// There are two modalities that want interrupts:
// - encoder ticks
// - bumpers
// So this file is generic to exti, not application of exti
//
namespace exti_line10 {
void boot_exti_line10(CounterOnPd10& counter, bte::ISystemClock& clock, GPIOPin pin)
{
    counter.set_clock(clock);

    LL_EXTI_InitTypeDef EXTI_InitStruct;
    gpio::Info          gpio = gpio::get(pin);

    LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTD, LL_GPIO_AF_EXTI_LINE10);
    EXTI_InitStruct.Line_0_31   = LL_EXTI_LINE_10;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode        = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger     = LL_EXTI_TRIGGER_RISING_FALLING;
    LL_EXTI_Init(&EXTI_InitStruct);

    LL_GPIO_SetPinMode(gpio.port, gpio.pin, LL_GPIO_MODE_FLOATING);
}
}  // namespace exti_line10

namespace exti_line11 {
void boot_exti_line11(CounterOnPd11& counter, bte::ISystemClock& clock, GPIOPin pin)
{
    counter.set_clock(clock);

    LL_EXTI_InitTypeDef EXTI_InitStruct;
    gpio::Info          gpio = gpio::get(pin);

    LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTD, LL_GPIO_AF_EXTI_LINE11);
    EXTI_InitStruct.Line_0_31   = LL_EXTI_LINE_11;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode        = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger     = LL_EXTI_TRIGGER_RISING_FALLING;
    LL_EXTI_Init(&EXTI_InitStruct);
    LL_GPIO_SetPinMode(gpio.port, gpio.pin, LL_GPIO_MODE_FLOATING);
}
}  // namespace exti_line11

namespace exti_line12 {
void boot_exti_line12(CounterOnPc12& counter, bte::ISystemClock& clock, GPIOPin pin)
{
    counter.set_clock(clock);

    LL_EXTI_InitTypeDef EXTI_InitStruct;
    gpio::Info          gpio = gpio::get(pin);

    LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTC, LL_GPIO_AF_EXTI_LINE12);
    EXTI_InitStruct.Line_0_31   = LL_EXTI_LINE_12;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode        = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger     = LL_EXTI_TRIGGER_RISING;
    LL_EXTI_Init(&EXTI_InitStruct);
    LL_GPIO_SetPinMode(gpio.port, gpio.pin, LL_GPIO_MODE_FLOATING);
}
}  // namespace exti_line12

namespace exti_line0 {
void boot_exti_line0(CounterOnPd0& counter, bte::ISystemClock& clock, GPIOPin pin)
{
    counter.set_clock(clock);

    LL_EXTI_InitTypeDef EXTI_InitStruct;
    gpio::Info          gpio = gpio::get(pin);

    LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTD, LL_GPIO_AF_EXTI_LINE0);
    EXTI_InitStruct.Line_0_31   = LL_EXTI_LINE_0;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode        = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger     = LL_EXTI_TRIGGER_RISING;
    LL_EXTI_Init(&EXTI_InitStruct);
    LL_GPIO_SetPinMode(gpio.port, gpio.pin, LL_GPIO_MODE_FLOATING);
}
}  // namespace exti_line0

}  // namespace stm32f1xx