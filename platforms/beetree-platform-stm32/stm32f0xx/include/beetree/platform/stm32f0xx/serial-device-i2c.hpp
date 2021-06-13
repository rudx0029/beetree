///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#pragma once

#include <utility>
#include "beetree/platform/i-serial-device.hpp"
#include "beetree/platform/i-system-clock.hpp"
#include "beetree/platform/basics/ring-q.hpp"
#include "beetree/platform/stm32f0xx/gpio-pin.hpp"
#include "beetree/platform/stm32f0xx/i2c-dev-id.hpp"

namespace stm32f0xx
{
    ///
    /// stm32f0xx Asynchronous Serial Interface for I2C devices.
    ///
    class SerialDevice_I2C : public bte::ISerialDevice
    {
    public:

        SerialDevice_I2C() = default;
        ///
        /// Invoked by `platform::boot()` to associate the usart with this
        /// instance
        ///
        /// @param id the usart associated with this instance
        ///
        void set_i2c(I2CDevID id) { m_i2c = id; }
        ///
        /// @return USARTDevID The usart this instance is associated with
        ///
        I2CDevID get_i2c() const { return m_i2c; }

        ///
        /// Invoked by `platform::boot()` to set the system clock
        ///
        /// @param clock the system clock
        ///
        void set_clock(bte::ISystemClock& clock) { m_clock = &clock; }

        ///
        /// Writes the data buffer to the serial device.
        ///
        /// @note
        /// The call blocks until all the data has been committed to the ring
        /// queue buffer or until the timeout has exceeded.
        ///
        /// @note
        /// The address is not supported and should be set to 0.
        ///
        /// @see
        /// platform::ISerialDevice::write
        ///
        int32_t write(std::size_t address,
                      const uint8_t* data,
                      std::size_t len,
                      bte::chrono::duration_ms timeout) override;
        ///
        /// Reads the requested number of bytes from the serial device into the
        /// data buffer.
        ///
        /// @ note
        /// The call blocks until the requested number of bytes have been
        /// received or the the timeout has exceeded.
        ///
        /// @note
        /// The address is not supported and should be set to 0.
        ///
        /// @see
        /// platform::ISerialDevice::read
        ///
        int32_t read(std::size_t address,
                     uint8_t* data,
                     std::size_t len,
                     bte::chrono::duration_ms timeout) override;

        uint8_t get_CHIP_ID() { return m_CHIP_ID; }
        uint8_t get_ACC_ID() { return m_ACC_ID; }
        uint8_t get_MAG_ID() { return m_MAG_ID; }
        uint8_t get_GYR_ID() { return m_GYR_ID; }

        void set_CHIP_ID(uint8_t id) { m_CHIP_ID = id; }
        void set_ACC_ID(uint8_t id) { m_ACC_ID = id; }
        void set_MAG_ID(uint8_t id) { m_MAG_ID = id; }
        void set_GYR_ID(uint8_t id) { m_GYR_ID = id; }

    private:
        bte::ISystemClock* m_clock;
        I2CDevID  m_i2c;
        uint8_t   m_CHIP_ID;
        uint8_t   m_MAG_ID;
        uint8_t   m_ACC_ID;
        uint8_t   m_GYR_ID;

    };
}  // namespace stm32f0xx