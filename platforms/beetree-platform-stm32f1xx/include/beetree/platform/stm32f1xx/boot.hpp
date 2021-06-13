///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file Boot definitions for stm32f1xx series devices and peripherals
///-----------------------------------------------------------------------------

#pragma once
#include "beetree/platform/stm32f1xx/counter.hpp"
#include "beetree/platform/stm32f1xx/discrete-input.hpp"
#include "beetree/platform/stm32f1xx/discrete-output.hpp"
#include "beetree/platform/stm32f1xx/serial-device-uart-dma.hpp"
#include "beetree/platform/stm32f1xx/system-clock.hpp"


namespace stm32f1xx {

///
/// Empty type for signalling a pin is not occupied
///
struct empty_t
{};
///
/// Empty variable to be used with boot(empty_t, pin);
///
constexpr empty_t empty;
///
/// Use to specify if a pin not occupied or being used.
///
inline void boot(empty_t, GPIOPin) {}

///
/// Boots and configures the Discrete Input, tying it to the GPIO pin.
///
/// @param din  the discrete input
/// @param pin  the gpio pin associated with the input
///
void boot(DiscreteInput& din, GPIOPin pin);

///
/// Boots and configures the Inverted Discrete Input, tying it to the GPIO pin.
///
/// @param din  the inverted discrete input
/// @param pin  the gpio pin associated with the input
///
void boot(DiscreteInputInv& din, GPIOPin pin);

///
/// Boots and configures the Discrete Output, tying it to the GPIO pin.
///
/// @param din  the inverted discrete output
/// @param pin  the gpio pin associated with the output
///
void boot(DiscreteOutput& dout, GPIOPin pin, bool mode_od = false);

///
/// Boots and configures the Inverted Discrete Output, tying it to the GPIO pin.
///
/// @param din  the inverted discrete output
/// @param pin  the gpio pin associated with the output
///
void boot(DiscreteOutputInv& dout, GPIOPin pin, bool mode_od = false);

///
/// Boots and configures a usart serial device with DMA, tying it to the given
/// usart
///
/// @param serial       the usart device
/// @param usart_id     the usart id, associating the the device `serial` to the
/// HW peripheral
/// @param tx_pin       the GPIO pin used to transmit on
/// @param rx_pin       the GPIO pin used to receive from
/// @param device_cfg   serial device settings such as baud rate, parity, etc.
/// @param clock        the system clock
///
void boot(SerialDevice_UART_DMA& serial,
          GPIOPin                tx_pin,
          GPIOPin                rx_pin,
          USARTDevID             usart_id,
          const SerialParams&    device_cfg,
          bte::ISystemClock&     clock);

///
/// Boots and configures the system clock
///
/// @param clk the system clock
///
void boot(SystemClock& clk);

///
/// TIM3 boot methods
///
namespace tim4 {
///
/// Boots timer 4 for use as a PWM on pins PD12 and PD13.
///     - GPIO Pin PD12 is TIM4's channel 1
///     - GPIO Pin PD13 is TIM4's channel 2
///
/// @param autoreload (default is 512) auto reload count which specifies the
/// frequency of the PWM
/// @param prescaler not sure?
///
void boot_pwm_pd12_pd13(uint32_t autoreload = 512, uint32_t prescaler = 2);
}  // namespace tim4

namespace exti_line10 {
void boot_exti_line10(CounterOnPd10&     counter,
                      bte::ISystemClock& clock,
                      GPIOPin            pin = GPIOPin::PD10);
}
namespace exti_line11 {
void boot_exti_line11(CounterOnPd11&     counter,
                      bte::ISystemClock& clock,
                      GPIOPin            pin = GPIOPin::PD11);
}

namespace exti_line12 {
void boot_exti_line12(CounterOnPc12&     counter,
                      bte::ISystemClock& clock,
                      GPIOPin            pin = GPIOPin::PC12);
}
namespace exti_line0 {
void boot_exti_line0(CounterOnPd0&      counter,
                     bte::ISystemClock& clock,
                     GPIOPin                 pin = GPIOPin::PD0);
}
}  // namespace stm32f1xx