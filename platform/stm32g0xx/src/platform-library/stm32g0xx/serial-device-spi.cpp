///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------


#include "platform-library/stm32g0xx/serial-device-spi.hpp"

namespace stm32g0xx
{
    void SerialDevice_SPI::enable_transfer(SPI_TypeDef* spi)
    {
        LL_SPI_EnableDMAReq_TX(spi);
        LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
        LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
    }

    void SerialDevice_SPI::disable_transfer(SPI_TypeDef* spi)
    {
        LL_DMA_DisableIT_TC(DMA1, LL_DMA_CHANNEL_1);
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
        LL_SPI_DisableDMAReq_TX(spi);
    }

    void SerialDevice_SPI::start_transfer(SPI_TypeDef* spi)
    {
        disable_transfer(spi);

        LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, buffer_elements*sizeof(uint32_t));
        LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, dma_buffer);

        enable_transfer(spi);
    }

    //
    // write not active on register reflection
    //
    int32_t SerialDevice_SPI::write(std::size_t address,
                                    const uint8_t* data,
                                    std::size_t len,
                                    bte::chrono::duration_ms timeout)
    {
        len = (len > buffer_elements) ? buffer_elements : len;
        const uint32_t *tmp = (const uint32_t *)(data);
        for(size_t i = 0; i<len; i++)
        {
            dma_buffer[i] = tmp[i];
        }

        start_transfer(spi::get(get_spi()));
        return 0;
    }
 
    int32_t SerialDevice_SPI::read(std::size_t address,
                                    uint8_t* data,
                                    std::size_t len,
                                    bte::chrono::duration_ms timeout)
    {
        return 0;
    }

    void SerialDevice_SPI::on_interrupt()
    {
        // /* Check whether DMA transfer complete caused the DMA interruption */
        if(LL_DMA_IsActiveFlag_TC1(DMA1) == 1)
        {
            volatile int count_out = 0;
            /* Clear flag DMA transfer complete */
            LL_DMA_ClearFlag_TC1(DMA1);
            
            while(LL_SPI_IsActiveFlag_BSY(spi::get(get_spi())))
            {
                //
                // Note - timing at 16 div is 8.5 us for completion.
                // It seems to happen faster than this loop.
                // Just make sure we don't get stuck.
                //
                if (count_out++ > 256) break;
            }

            disable_transfer(spi::get(get_spi()));
        }
        // /* Check whether DMA half transfer caused the DMA interruption */
        if(LL_DMA_IsActiveFlag_HT1(DMA1) == 1)
        {
            /* Clear flag DMA half transfer */
            LL_DMA_ClearFlag_HT1(DMA1);
        }
        // // /* Check whether DMA transfer error caused the DMA interruption */
        if(LL_DMA_IsActiveFlag_TE1(DMA1) == 1)
        {
            /* Clear flag DMA transfer error */
            LL_DMA_ClearFlag_TE1(DMA1);
        }
    }

}  // namespace stm32g0xx