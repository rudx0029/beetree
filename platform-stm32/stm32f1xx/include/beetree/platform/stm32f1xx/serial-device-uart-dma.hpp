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
#include "beetree/platform/ring-q.hpp"
#include "beetree/platform/stm32f1xx/gpio-pin.hpp"
#include "beetree/platform/stm32f1xx/serial-params.hpp"
#include "beetree/platform/stm32f1xx/usart-dev-id.hpp"

namespace stm32f1xx {
///
/// stm32f1xx Asynchronous Serial Interface for USART devices with DMA
/// support.
///
/// When transmitting, the interface buffers the data into a `BUFF_LEN` ring
/// queue before transmitting. The DMA then 'drains' the buffer and
/// transmits the data. Likewise, the interface will buffer received data
/// into a ring queue. However, the oldest data will be overriden if the
/// application does not 'read' the data.
///
class SerialDevice_UART_DMA : public bte::ISerialDevice
{
public:
    static constexpr std::size_t BUFF_LEN{64};  ///< ring queue buffer size
    static constexpr std::size_t DMA_BUFF_LEN{4 * sizeof(uint32_t)};

    SerialDevice_UART_DMA() = default;
    ///
    /// Invoked by `platform::boot()` to associate the usart with this
    /// instance
    ///
    /// @param id the usart associated with this instance
    ///
    void set_usart(USARTDevID id) { m_usart = id; }
    ///
    /// Invoked by `platform::boot()` to set the system clock
    ///
    /// @param clock the system clock
    ///
    void set_clock(bte::ISystemClock& clock) { m_clock = &clock; }
    ///
    /// @return USARTDevID The usart this instance is associated with
    ///
    USARTDevID get_usart() const { return m_usart; }
    ///
    /// @return uint8_t* The DMA recieve buffer
    ///
    uint8_t* get_rx_dma_buff() { return m_rx_dma_buff; }
    ///
    /// @return uint8_t* The DMA transmit buffer
    ///
    uint8_t* get_tx_dma_buff() { return m_tx_dma_buff; }  ///< @return The DMA transmit buffer
    ///
    /// Invoked by a DMA channel interrupt to handler to process any data
    /// transfers between the ring queues and the deivce
    ///
    void on_dma_interrupt();  ///< handles usart dma interrupts
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
    /// bte::ISerialDevice::write
    ///
    int32_t write(std::size_t              address,
                  const uint8_t*           data,
                  std::size_t              len,
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
    /// bte::ISerialDevice::read
    ///
    int32_t read(std::size_t              address,
                 uint8_t*           data,
                 std::size_t              len,
                 bte::chrono::duration_ms timeout) override;

private:
    uint8_t m_tx_dma_buff[DMA_BUFF_LEN];
    uint8_t m_rx_dma_buff[DMA_BUFF_LEN];

    platform::RingQContainer<BUFF_LEN> m_rx_q;
    platform::RingQContainer<BUFF_LEN> m_tx_q;

    bte::ISystemClock* m_clock;
    USARTDevID         m_usart;
};
}  // namespace stm32f1xx