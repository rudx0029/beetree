#include "beetree/platform/stm32f1xx/boot.hpp"
#include "beetree/platform/stm32f1xx/discrete-input.hpp"
#include "beetree/platform/stm32f1xx/discrete-output.hpp"
#include "beetree/platform/stm32f1xx/hal/stm32f1xx_ll_bus.h"
#include "beetree/platform/stm32f1xx/hal/stm32f1xx_ll_dma.h"
#include "beetree/platform/stm32f1xx/hal/stm32f1xx_ll_gpio.h"
#include "beetree/platform/stm32f1xx/hal/stm32f1xx_ll_usart.h"
#include "beetree/platform/stm32f1xx/helpers.hpp"

namespace stm32f1xx {
static void init_device(USARTDevID          usart_id,
                        GPIOPin             tx_pin,
                        GPIOPin             rx_pin,
                        const SerialParams& serial_params)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    /**USART GPIO Configuration
     */
    GPIO_InitStruct.Pin        = gpio::get(tx_pin).pin;
    GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(gpio::get(tx_pin).port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = gpio::get(rx_pin).pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;  // LL_GPIO_MODE_ALTERNATE;
    LL_GPIO_Init(gpio::get(rx_pin).port, &GPIO_InitStruct);

    /* USART DMA Init */

    /* USART_RX Init */
    DMA_TypeDef* dma            = usart::get_dma_info(usart_id).dma;
    uint32_t     dma_rx_channel = usart::get_dma_info(usart_id).rx_channel;
    uint32_t     dma_tx_channel = usart::get_dma_info(usart_id).tx_channel;

    LL_DMA_SetDataTransferDirection(dma, dma_rx_channel, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

    LL_DMA_SetChannelPriorityLevel(dma, dma_rx_channel, LL_DMA_PRIORITY_LOW);

    LL_DMA_SetMode(dma, dma_rx_channel, LL_DMA_MODE_NORMAL);

    LL_DMA_SetPeriphIncMode(dma, dma_rx_channel, LL_DMA_PERIPH_NOINCREMENT);

    LL_DMA_SetMemoryIncMode(dma, dma_rx_channel, LL_DMA_MEMORY_INCREMENT);

    LL_DMA_SetPeriphSize(dma, dma_rx_channel, LL_DMA_PDATAALIGN_BYTE);

    LL_DMA_SetMemorySize(dma, dma_rx_channel, LL_DMA_MDATAALIGN_BYTE);

    /* USART_TX Init */
    LL_DMA_SetDataTransferDirection(dma, dma_tx_channel, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

    LL_DMA_SetChannelPriorityLevel(dma, dma_tx_channel, LL_DMA_PRIORITY_LOW);

    LL_DMA_SetMode(dma, dma_tx_channel, LL_DMA_MODE_NORMAL);

    LL_DMA_SetPeriphIncMode(dma, dma_tx_channel, LL_DMA_PERIPH_NOINCREMENT);

    LL_DMA_SetMemoryIncMode(dma, dma_tx_channel, LL_DMA_MEMORY_INCREMENT);

    LL_DMA_SetPeriphSize(dma, dma_tx_channel, LL_DMA_PDATAALIGN_BYTE);

    LL_DMA_SetMemorySize(dma, dma_tx_channel, LL_DMA_MDATAALIGN_BYTE);

    /* USART interrupt Init */
    USART_TypeDef* usart = usart::get(usart_id);
    //    IRQn_Type            irq    = usart::get_irq(usart_id);
    LL_USART_InitTypeDef devcfg = usart::to_stm(serial_params);

    // NVIC_SetPriority(irq, 0);
    //    NVIC_SetPriority(irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    //    NVIC_EnableIRQ(irq);

    LL_USART_Init(usart, &devcfg);
    LL_USART_DisableIT_CTS(usart);
    LL_USART_ConfigAsyncMode(usart);
    LL_USART_Enable(usart);
}

void boot(SerialDevice_UART_DMA& serial,
          GPIOPin                tx_pin,
          GPIOPin                rx_pin,
          USARTDevID             usart_id,
          const SerialParams&    device_cfg,
          bte::ISystemClock&     clock)
{
    serial.set_usart(usart_id);
    serial.set_clock(clock);

    init_device(usart_id, tx_pin, rx_pin, device_cfg);

    USART_TypeDef* usart    = usart::get(usart_id);
    usart::DmaInfo dma_info = usart::get_dma_info(usart_id);
    LL_DMA_ConfigAddresses(dma_info.dma,
                           dma_info.tx_channel,
                           (uint32_t)serial.get_tx_dma_buff(),
                           LL_USART_DMA_GetRegAddr(usart),
                           LL_DMA_GetDataTransferDirection(dma_info.dma, dma_info.tx_channel));

    // LL_USART_EnableDMAReq_RX(USART2);
    // LL_USART_EnableIT_IDLE(USART2);

    /* Polling USART initialisation */
    while (LL_USART_IsEnabledDMAReq_TX(usart))
    {
    }
}
}  // namespace stm32f1xx