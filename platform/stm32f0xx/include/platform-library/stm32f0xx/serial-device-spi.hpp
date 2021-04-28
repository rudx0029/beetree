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
#include <stdalign.h>
#include "beetree/platform/i-serial-device.hpp"
#include "beetree/platform/i-system-clock.hpp"
#include "platform-library/stm32f0xx/spi-dev-id.hpp"

namespace stm32f0xx
{
    //
    // 4 by 32 bit (4 bytes)
    //
    #define NFM_DATA_BUFFER_ELEMENT_SIZE 4
    #define NFM_DATA_BUFFER_SIZE 6
    #define NFM_DATA_BUFFER_BYTES (NFM_DATA_BUFFER_SIZE * NFM_DATA_BUFFER_ELEMENT_SIZE)
    extern uint32_t spi_buffer[NFM_DATA_BUFFER_SIZE];
    ///
    /// stm32f0xx Asynchronous Serial Interface for I2C devices.
    ///
    class SerialDevice_SPI : public bte::ISerialDevice
    {
    public:

        SerialDevice_SPI() = default;
        ///
        /// Invoked by `platform::boot()` to associate the usart with this
        /// instance
        ///
        /// @param id the usart associated with this instance
        ///
        void set_spi(SPIDevID id) { m_spi = id; }
        ///
        /// @return USARTDevID The usart this instance is associated with
        ///
        SPIDevID get_spi() const { return m_spi; }

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

        void on_interrupt(void );
        void enable_transfer(SPI_TypeDef* spi);
        void disable_transfer(SPI_TypeDef* spi);
        void start_transfer(SPI_TypeDef* spi);

        int buffer_elements = 0;
        uint32_t *dma_buffer = nullptr;
        uint32_t *copy_buffer = nullptr;

    private:
        bte::ISystemClock* m_clock;
        SPIDevID  m_spi;
        bool m_pending = false;
    };
}  // namespace stm32f0xx