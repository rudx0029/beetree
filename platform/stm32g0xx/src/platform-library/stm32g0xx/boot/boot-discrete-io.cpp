#include "platform-library/stm32g0xx/boot.hpp"
#include "platform-library/stm32g0xx/discrete-input.hpp"
#include "platform-library/stm32g0xx/discrete-output.hpp"
#include "platform-library/stm32g0xx/hal/stm32g0xx_ll_gpio.h"
#include "platform-library/stm32g0xx/helpers.hpp"

namespace stm32g0xx
{
    static void boot_din(GPIOPin pin)
    {
        gpio::Info gpio = gpio::get(pin);

        LL_GPIO_InitTypeDef GPIO_InitStruct;

        GPIO_InitStruct.Pin = gpio.pin;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
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

    void boot_dout(GPIOPin pin)
    {
        gpio::Info gpio = gpio::get(pin);

        LL_GPIO_InitTypeDef GPIO_InitStruct;

        LL_GPIO_ResetOutputPin(gpio.port, gpio.pin);
        GPIO_InitStruct.Pin = gpio.pin;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
        LL_GPIO_Init(gpio.port, &GPIO_InitStruct);
    }
    void boot(DiscreteOutput& dout, GPIOPin pin)
    {
        dout.set_pin(pin);
        boot_dout(pin);
    }

    void boot(DiscreteOutputInv& dout, GPIOPin pin)
    {
        dout.set_pin(pin);
        boot_dout(pin);
    }

}  // namespace stm32g0xx