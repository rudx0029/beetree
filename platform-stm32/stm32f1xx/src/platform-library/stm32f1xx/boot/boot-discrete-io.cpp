#include "platform-library/stm32f1xx/boot.hpp"
#include "platform-library/stm32f1xx/discrete-input.hpp"
#include "platform-library/stm32f1xx/discrete-output.hpp"
#include "platform-library/stm32f1xx/hal/stm32f1xx_ll_gpio.h"
#include "platform-library/stm32f1xx/helpers.hpp"

namespace stm32f1xx
{
    static void boot_din(GPIOPin pin)
    {
        gpio::Info gpio = gpio::get(pin);

        LL_GPIO_InitTypeDef GPIO_InitStruct;

        GPIO_InitStruct.Pin = gpio.pin;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
        LL_GPIO_Init(gpio.port, &GPIO_InitStruct);
    }

    void boot(DiscreteInput& d, GPIOPin pin)
    {
        d.set_pin(pin);
        boot_din(pin);
    }
    void boot(DiscreteInputInv& d, GPIOPin pin)
    {
        d.set_pin(pin);
        boot_din(pin);
    }

    void boot_dout(GPIOPin pin, bool mode_od)
    {
        gpio::Info gpio = gpio::get(pin);

        LL_GPIO_InitTypeDef GPIO_InitStruct;

        LL_GPIO_ResetOutputPin(gpio.port, gpio.pin);
        GPIO_InitStruct.Pin = gpio.pin;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.OutputType = mode_od ? LL_GPIO_OUTPUT_OPENDRAIN : LL_GPIO_OUTPUT_PUSHPULL;
        LL_GPIO_Init(gpio.port, &GPIO_InitStruct);
    }
    void boot(DiscreteOutput& dout, GPIOPin pin, bool mode_od)
    {
        dout.set_pin(pin);
        boot_dout(pin, mode_od);
    }

    void boot(DiscreteOutputInv& dout, GPIOPin pin, bool mode_od)
    {
        dout.set_pin(pin);
        boot_dout(pin, mode_od);
    }

}  // namespace stm32f1xx