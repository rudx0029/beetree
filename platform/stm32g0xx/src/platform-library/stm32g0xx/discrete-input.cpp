///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "platform-library/stm32g0xx/discrete-input.hpp"
#include "platform-library/stm32g0xx/hal/stm32g0xx_ll_gpio.h"
#include "platform-library/stm32g0xx/helpers.hpp"

namespace stm32g0xx
{
    namespace discrete_input
    {
        bool is_set(GPIOPin pin)
        {
            gpio::Info gpio = gpio::get(pin);
            return LL_GPIO_IsInputPinSet(gpio.port, gpio.pin);
        }
    }  // namespace discrete_input

}  // namespace stm32f0xx