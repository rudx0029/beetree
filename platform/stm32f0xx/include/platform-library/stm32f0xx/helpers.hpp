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
#include "platform-library/stm32f0xx/gpio-pin.hpp"
#include "platform-library/stm32f0xx/hal/stm32f0xx_ll_usart.h"
#include "platform-library/stm32f0xx/hal/stm32f0xx_ll_i2c.h"
#include "platform-library/stm32f0xx/serial-params.hpp"
#include "platform-library/stm32f0xx/system/stm32f0xx.h"
#include "platform-library/stm32f0xx/usart-dev-id.hpp"
#include "platform-library/stm32f0xx/i2c-dev-id.hpp"
#include "platform-library/stm32f0xx/spi-dev-id.hpp"

namespace stm32f0xx
{
    namespace gpio
    {
        struct Info
        {
            GPIO_TypeDef* port;
            std::size_t pin;
        };

        Info get(GPIOPin pin);
    }  // namespace gpio

    namespace usart
    {
        struct DmaInfo
        {
            DMA_TypeDef* dma;
            uint32_t rx_channel;
            uint32_t tx_channel;
        };

        USART_TypeDef* get(USARTDevID usart);
        LL_USART_InitTypeDef to_stm(const SerialParams& params);

        DmaInfo get_dma_info(USARTDevID uart);
        IRQn_Type get_irq(USARTDevID uart);
    }  // namespace usart

    namespace dma
    {
        bool is_transfer_complete(DMA_TypeDef* dma, uint32_t channel);
        void clear_transfer_complete_flag(DMA_TypeDef* dma, uint32_t channel);
    }  // namespace dma

    namespace i2c
    {
        I2C_TypeDef* get(I2CDevID i2c);
    }

    namespace spi
    {
        SPI_TypeDef* get(SPIDevID spi);
    }

}  // namespace stm32f0xx