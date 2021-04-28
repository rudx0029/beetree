///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------


#include "platform-library/stm32f0xx/serial-device-spi.hpp"

namespace stm32f0xx
{
    void SerialDevice_SPI::enable_transfer(SPI_TypeDef* spi)
    {
        LL_SPI_EnableDMAReq_RX(spi);
        LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
        LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
    }

    void SerialDevice_SPI::disable_transfer(SPI_TypeDef* spi)
    {
        LL_DMA_DisableIT_TC(DMA1, LL_DMA_CHANNEL_2);
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
        LL_SPI_DisableDMAReq_RX(spi);
    }

    void SerialDevice_SPI::start_transfer(SPI_TypeDef* spi)
    {
        disable_transfer(spi);

        LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, buffer_elements*sizeof(uint32_t));
        LL_DMA_SetMemoryAddress(DMA1,LL_DMA_CHANNEL_2, dma_buffer);

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
        return 0;
    }

    int32_t SerialDevice_SPI::read(std::size_t address,
                                    uint8_t* data,
                                    std::size_t len,
                                    bte::chrono::duration_ms timeout)
    {
        len = (len > buffer_elements) ? buffer_elements : len;
        uint32_t *tmp = (uint32_t *)(data);
        for(std::size_t i=0; i<len; i++)
        {
            tmp[i] = copy_buffer[i];
        }            
        return len;
    }

    void SerialDevice_SPI::on_interrupt()
    {
        // /* Check whether DMA transfer complete caused the DMA interruption */
        if(LL_DMA_IsActiveFlag_TC2(DMA1) == 1)
        {
            // volatile int count_out = 0;
            /* Clear flag DMA transfer complete */
            for(std::size_t i=0; i<NFM_DATA_BUFFER_SIZE; i++)
            {
                copy_buffer[i] = dma_buffer[i];
            }
            LL_DMA_ClearFlag_TC2(DMA1);
            //
            // Need to reset the buffer to keep things in sync. in lue of failure.
            //
            LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, buffer_elements*sizeof(uint32_t));
            LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_2, dma_buffer);
            enable_transfer(spi::get(get_spi()));
        }

        // /* Check whether DMA half transfer caused the DMA interruption */
        if(LL_DMA_IsActiveFlag_HT2(DMA1) == 1)
        {
            /* Clear flag DMA half transfer */
            LL_DMA_ClearFlag_HT2(DMA1);
        }
        // // /* Check whether DMA transfer error caused the DMA interruption */
        if(LL_DMA_IsActiveFlag_TE2(DMA1) == 1)
        {
            /* Clear flag DMA transfer error */
            LL_DMA_ClearFlag_TE2(DMA1);
        }
    }
}  // namespace stm32f0xx