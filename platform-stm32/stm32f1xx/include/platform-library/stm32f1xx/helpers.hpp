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
#include "platform-library/stm32f1xx/gpio-pin.hpp"
#include "platform-library/stm32f1xx/hal/stm32f1xx_ll_usart.h"
#include "platform-library/stm32f1xx/serial-params.hpp"
#include "platform-library/stm32f1xx/system/stm32f1xx.h"
#include "platform-library/stm32f1xx/usart-dev-id.hpp"

namespace stm32f1xx
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

}  // namespace stm32f1xx