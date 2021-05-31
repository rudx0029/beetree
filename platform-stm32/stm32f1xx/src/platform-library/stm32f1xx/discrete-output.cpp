///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "platform-library/stm32f1xx/discrete-output.hpp"
#include "platform-library/stm32f1xx/hal/stm32f1xx_ll_gpio.h"
#include "platform-library/stm32f1xx/helpers.hpp"

namespace stm32f1xx
{
    namespace discrete_output
    {
        void set(GPIOPin pin)
        {
            gpio::Info gpio = gpio::get(pin);
            LL_GPIO_SetOutputPin(gpio.port, gpio.pin);
        }
        void clear(GPIOPin pin)
        {
            gpio::Info gpio = gpio::get(pin);
            LL_GPIO_ResetOutputPin(gpio.port, gpio.pin);
        }
        bool is_set(GPIOPin pin)
        {
            gpio::Info gpio = gpio::get(pin);
            return LL_GPIO_IsOutputPinSet(gpio.port, gpio.pin);
        }
        void toggle(GPIOPin pin)
        {
            gpio::Info gpio = gpio::get(pin);
            LL_GPIO_TogglePin(gpio.port, gpio.pin);
        }
    }  // namespace discrete_output

}  // namespace stm32f1xx