///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file Boot definitions for stm32f0xx series devices and peripherals
///-----------------------------------------------------------------------------

#pragma once
#include "platform-library/stm32g0xx/counter.hpp"
#include "platform-library/stm32g0xx/discrete-input.hpp"
#include "platform-library/stm32g0xx/discrete-output.hpp"
#include "platform-library/stm32g0xx/serial-device-uart-dma.hpp"
#include "platform-library/stm32g0xx/serial-device-i2c.hpp"
#include "platform-library/stm32g0xx/system-clock.hpp"

namespace stm32g0xx {

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
void boot(DiscreteOutput& dout, GPIOPin pin);

///
/// Boots and configures the Inverted Discrete Output, tying it to the GPIO pin.
///
/// @param din  the inverted discrete output
/// @param pin  the gpio pin associated with the output
///
void boot(DiscreteOutputInv& dout, GPIOPin pin);

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
/// Boots and configures an i2c serial device, tying it to the given
/// spi
///
/// @param serial       the spi device
/// @param I2CDevID     the ID to get to the correct type
/// @param clock        the system clock
/// @param buffer_elements buffer type size
/// @param dma_buffer       buffer
/// @param copy_buffer      used to double buffer input
///
void boot(SerialDevice_SPI&  serial, 
        SPIDevID spi_id, 
        bte::ISystemClock& clock,
        int buffer_elements,
        uint32_t *dma_buffer);

///
/// Boots and configures an i2c serial device, tying it to the given
/// i2c
///
/// @param serial       the i2c device
/// @param I2CDevID     the ID to get to the correct type
/// @param clock        the system clock
///
void boot(SerialDevice_I2C&  serial, I2CDevID i2c_id, bte::ISystemClock& clock);

///
/// Boots and configures the system clock
///
/// @param clk the system clock
///
void boot(SystemClock& clk);

namespace tim1 {
void boot_counter_pa8(uint32_t autoreload = 32768, uint32_t prescaler = 0);
}  // namespace tim1

namespace tim3 {
void boot_counter_pb4(uint32_t autoreload = 32768, uint32_t prescaler = 0);
}  // namespace tim3

namespace tim14 {
///
/// Boots timer 14 for use as a PWM on pin pa7.
///
/// @param autoreload (default is 512) auto reload count which specifies the
/// frequency of the PWM
/// @param prescaler not sure?
///
void boot_pwm_pa7(uint32_t autoreload = 512, uint32_t prescaler = 2);
}  // namespace tim3

namespace tim16 {
///
/// Boots timer 16 for use as a PWM on pin pa7.
///
/// @param autoreload (default is 512) auto reload count which specifies the
/// frequency of the PWM
/// @param prescaler not sure?
///
void boot_pwm_pa6(uint32_t autoreload = 512, uint32_t prescaler = 2);
}  // namespace tim3

namespace exti_line1 {
void boot_exti_line1(CounterOnPa1& counter, bte::ISystemClock& clock);
}

namespace exti_line2 {
void boot_exti_line2(CounterOnPb2& counter, bte::ISystemClock& clock);
}

}  // namespace stm32g0xx