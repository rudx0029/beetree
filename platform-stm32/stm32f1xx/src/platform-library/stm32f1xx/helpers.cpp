///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "platform-library/stm32f1xx/helpers.hpp"
#include "platform-library/stm32f1xx/hal/stm32f1xx_ll_bus.h"
#include "platform-library/stm32f1xx/hal/stm32f1xx_ll_dma.h"
#include "platform-library/stm32f1xx/hal/stm32f1xx_ll_gpio.h"
#include "platform-library/stm32f1xx/hal/stm32f1xx_ll_usart.h"
#include "platform-library/stm32f1xx/system/stm32f1xx.h"

namespace stm32f1xx
{
    // > Internal Methods
    namespace gpio
    {
        GPIO_TypeDef* port_idx_to_stm(std::size_t port_idx)
        {
            switch (port_idx)
            {
#if defined(GPIOA)
                case 0:
                    return GPIOA;
#endif
#if defined(GPIOB)
                case 1:
                    return GPIOB;
#endif
#if defined(GPIOC)
                case 2:
                    return GPIOC;
#endif
#if defined(GPIOD)
                case 3:
                    return GPIOD;
#endif
#if defined(GPIOE)
                case 4:
                    return GPIOE;
#endif
#if defined(GPIOF)
                case 5:
                    return GPIOF;
#endif
#if defined(GPIOG)
                case 6:
                    return GPIOG;
#endif
                default:
                    return nullptr;
            }
        }

        constexpr std::size_t pin_table_f1[16] = {
            LL_GPIO_PIN_0,
            LL_GPIO_PIN_1,
            LL_GPIO_PIN_2,
            LL_GPIO_PIN_3,
            LL_GPIO_PIN_4,
            LL_GPIO_PIN_5,
            LL_GPIO_PIN_6,
            LL_GPIO_PIN_7,
            LL_GPIO_PIN_8,
            LL_GPIO_PIN_9,
            LL_GPIO_PIN_10,
            LL_GPIO_PIN_11,
            LL_GPIO_PIN_12,
            LL_GPIO_PIN_13,
            LL_GPIO_PIN_14,
            LL_GPIO_PIN_15
        };

        std::size_t pin_idx_to_stm(std::size_t pin_idx) { return pin_table_f1[pin_idx]; }

        // > Public API

        gpio::Info get(GPIOPin pin)
        {
            std::size_t p = static_cast<std::size_t>(pin);
            std::size_t pin_idx = (p & 0x0F);
            std::size_t port_idx = (p & 0xF0) >> 4;

            return gpio::Info{port_idx_to_stm(port_idx), pin_idx_to_stm(pin_idx)};
        }
    }  // namespace gpio

    namespace usart
    {
        USART_TypeDef* get(USARTDevID uart)
        {
            switch (uart)
            {
                default:
                case USARTDevID::USART_1:
                    return USART1;
//                case USARTDevID::USART_2:
//                    return USART2;
            }
        }

        LL_USART_InitTypeDef to_stm(const SerialParams& params)
        {
            LL_USART_InitTypeDef ncfg;

            ncfg.BaudRate = params.baud_rate;

            switch (params.data_width)
            {
                case DataWidth::NINE:
                    ncfg.DataWidth = LL_USART_DATAWIDTH_9B;
                    break;
                default:
                    ncfg.DataWidth = LL_USART_DATAWIDTH_8B;
                    break;
            }

            switch (params.parity)
            {
                case Parity::EVEN:
                    ncfg.Parity = LL_USART_PARITY_EVEN;
                    break;
                case Parity::ODD:
                    ncfg.Parity = LL_USART_PARITY_ODD;
                    break;
                default:
                    ncfg.Parity = LL_USART_PARITY_NONE;
                    break;
            }

            switch (params.stop_bits)
            {
                case StopBits::TWO:
                    ncfg.StopBits = LL_USART_STOPBITS_2;
                    break;
                default:
                    ncfg.StopBits = LL_USART_STOPBITS_1;
                    break;
            }

            ncfg.TransferDirection = LL_USART_DIRECTION_TX_RX;
            ncfg.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
//            ncfg.OverSampling = LL_USART_OVERSAMPLING_16;

            return ncfg;
        }

        DmaInfo get_dma_info(USARTDevID uart)
        {
            switch (uart)
            {
                default:
                case USARTDevID::USART_1:
                    return DmaInfo{DMA1, LL_DMA_CHANNEL_5, LL_DMA_CHANNEL_4};
//                case USARTDevID::USART_2:
//                    return DmaInfo{DMA1, LL_DMA_CHANNEL_5, LL_DMA_CHANNEL_4};
            }
        }

        IRQn_Type get_irq(USARTDevID uart)
        {
            switch (uart)
            {
                default:
                case USARTDevID::USART_1:
                    return USART1_IRQn;
//                case USARTDevID::USART_2:
//                    return USART2_IRQn;
            }
        }
    }  // namespace usart

    namespace dma
    {
        bool is_transfer_complete(DMA_TypeDef* dma, uint32_t channel)
        {
            switch (channel)
            {
                case LL_DMA_CHANNEL_1:
                    return LL_DMA_IsActiveFlag_TC1(dma);
                case LL_DMA_CHANNEL_2:
                    return LL_DMA_IsActiveFlag_TC2(dma);
                case LL_DMA_CHANNEL_3:
                    return LL_DMA_IsActiveFlag_TC3(dma);
                case LL_DMA_CHANNEL_4:
                    return LL_DMA_IsActiveFlag_TC4(dma);
                case LL_DMA_CHANNEL_5:
                    return LL_DMA_IsActiveFlag_TC5(dma);
                default:
                    return false;
            }
        }

        void clear_transfer_complete_flag(DMA_TypeDef* dma, uint32_t channel)
        {
            switch (channel)
            {
                case LL_DMA_CHANNEL_1:
                    LL_DMA_ClearFlag_TC1(dma);
                    return;
                case LL_DMA_CHANNEL_2:
                    LL_DMA_ClearFlag_TC2(dma);
                    return;
                case LL_DMA_CHANNEL_3:
                    LL_DMA_ClearFlag_TC3(dma);
                    return;
                case LL_DMA_CHANNEL_4:
                    LL_DMA_ClearFlag_TC4(dma);
                    return;
                case LL_DMA_CHANNEL_5:
                    LL_DMA_ClearFlag_TC5(dma);
                    return;
                default:
                    return;
            }
        }
    }  // namespace dma

}  // namespace stm32f0xx