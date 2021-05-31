///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "beetree/platform/stm32f0xx/serial-device-uart-dma.hpp"
#include "beetree/platform/stm32f0xx/hal/stm32f0xx_ll_dma.h"
#include "beetree/platform/stm32f0xx/hal/stm32f0xx_ll_usart.h"
#include "beetree/platform/stm32f0xx/helpers.hpp"

namespace stm32f0xx {
void enable_transfer(USART_TypeDef* usart, const usart::DmaInfo& dma_info)
{
    LL_USART_EnableDMAReq_TX(usart);
    LL_DMA_EnableChannel(dma_info.dma, dma_info.tx_channel);
    LL_DMA_EnableIT_TC(dma_info.dma, dma_info.tx_channel);
    // LL_DMA_EnableIT_TE(m_dma);
}

void disable_transfer(USART_TypeDef* usart, const usart::DmaInfo& dma_info)
{
    LL_DMA_DisableIT_TC(dma_info.dma, dma_info.tx_channel);
    // LL_DMA_EnableIT_TE(m_dma);
    LL_DMA_DisableChannel(dma_info.dma, dma_info.tx_channel);
    LL_USART_DisableDMAReq_TX(usart);
}

void start_transfer(USART_TypeDef*        usart,
                    const usart::DmaInfo& dma_info,
                    platform::RingQ&      q,
                    uint8_t*              buff,
                    std::size_t           len)
{
    disable_transfer(usart, dma_info);

    // transfer the q to the dma buffer
    uint32_t nTx = 0;
    for (; nTx < len && q.count() > 0; nTx++)
    {
        buff[nTx] = q.pop();
    }

    LL_DMA_SetDataLength(dma_info.dma, dma_info.tx_channel, nTx);

    enable_transfer(usart, dma_info);
}

void SerialDevice_UART_DMA::on_dma_interrupt()
{
    usart::DmaInfo dma_info = usart::get_dma_info(m_usart);

    if (dma::is_transfer_complete(dma_info.dma, dma_info.tx_channel))
    {
        dma::clear_transfer_complete_flag(dma_info.dma, dma_info.tx_channel);
        if (m_tx_q->count() > 0)
        {
            // restart the transfer if app is not actively calling
            // vcp_tx
            start_transfer(usart::get(m_usart), dma_info, *m_tx_q, m_tx_dma_buff, DMA_BUFF_LEN);
        }
        else
        {
            disable_transfer(usart::get(m_usart), dma_info);
        }
    }
}

///
/// [Spin] Waits for the Q to have `nbytes` storage while checking for a
/// timeout condition.
///
/// @param q the ring Q context to wait on
/// @param nbytes the number of bytes requested
/// @param clock the system clock
/// @param start the timepoint that the operation began
/// @param timeout the max duration of the operation
///
/// @return true after successfully waiting on the queue to free up `nbytes`
/// @return false a timeout occured while waiting for the q to free up
/// space.
///
bool wait_for_ready(platform::RingQ&          q,
                    uint32_t                  nbytes,
                    bte::ISystemClock*        clock,
                    bte::chrono::timepoint_ms start,
                    bte::chrono::duration_ms  timeout)
{
    bool is_timeout = false;
    bool is_ready   = false;

    do
    {
        is_ready   = (nbytes + q.count()) <= q.capacity();
        is_timeout = (clock->now_ms() - start) > timeout;
    } while (!is_timeout && !is_ready);

    return !is_timeout;
}

int32_t SerialDevice_UART_DMA::write(std::size_t              address,
                                     const uint8_t*           data,
                                     std::size_t              len,
                                     bte::chrono::duration_ms timeout)
{
    ((void)address);  // not used
    USART_TypeDef*            usart    = usart::get(m_usart);
    usart::DmaInfo            dma_info = usart::get_dma_info(m_usart);
    bte::chrono::timepoint_ms start    = m_clock->now_ms();

    while (len > 0)
    {
        uint32_t nqueued = 0;
        uint32_t nbytes  = len <= m_tx_q->capacity() ? len : m_tx_q->capacity();

        if (wait_for_ready(*m_tx_q, nbytes, m_clock, start, timeout))
        {
            // push the requested data onto the ring buffer,
            // while disabling the dma interrupt on each push
            for (; nqueued < nbytes; nqueued++)
            {
                LL_DMA_DisableIT_TC(dma_info.dma, dma_info.tx_channel);
                m_tx_q->push(data[nqueued]);
                LL_DMA_EnableIT_TC(dma_info.dma, dma_info.tx_channel);
            }

            // start a tranfer if one doesn't already exist
            if (nqueued > 0 && !LL_USART_IsEnabledDMAReq_TX(usart))
            {
                start_transfer(usart, dma_info, *m_tx_q, m_tx_dma_buff, DMA_BUFF_LEN);
            }

            len -= nbytes;
        }
        else
        {
            break;  // < timeout occurred
        }
    }

    return len;
}
int32_t SerialDevice_UART_DMA::read(std::size_t              address,
                                    uint8_t*           data,
                                    std::size_t              len,
                                    bte::chrono::duration_ms timeout)
{
    return 0;
}

}  // namespace stm32f0xx