
#include <stdalign.h>

#include "../hal/stm32g0xx_ll_bus.h"
#include "../hal/stm32g0xx_ll_dma.h"
#include "../hal/stm32g0xx_ll_gpio.h"
#include "../hal/stm32g0xx_ll_spi.h"

#include "platform-library/stm32g0xx/boot.hpp"
#include "platform-library/stm32g0xx/discrete-input.hpp"
#include "platform-library/stm32g0xx/discrete-output.hpp"
#include "platform-library/stm32g0xx/helpers.hpp"

#include "platform-library/stm32g0xx/serial-device-spi.hpp"

namespace stm32g0xx {

    // user boot application
    // uint32_t spi_buffer[NFM_DATA_BUFFER_SIZE] alignas(32) ;

    void boot_spi1_pa1_pa7(SPI_TypeDef* SPIx, uint32_t* image_buffer, int buffer_length)
    {
        LL_SPI_InitTypeDef SPI_InitStruct = {0};
        LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

       /**SPI1 GPIO Configuration
        PA1   ------> SPI1_SCK
        PA7   ------> SPI1_MOSI
        */
        GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
        GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
        LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
        GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
        LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* SPI1_TX Init */
        LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_SPI1_TX);
        LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
        LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_LOW);
        LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_NORMAL); //LL_DMA_MODE_CIRCULAR);
        LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
        LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
        LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_BYTE);
        LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_BYTE);
 
        LL_DMA_SetDataLength(DMA1,LL_DMA_CHANNEL_1,  buffer_length);
        LL_DMA_SetPeriphAddress(DMA1,LL_DMA_CHANNEL_1, LL_SPI_DMA_GetRegAddr(SPIx));
        LL_DMA_SetMemoryAddress(DMA1,LL_DMA_CHANNEL_1, (uint32_t )image_buffer);

        /* SPI1 parameter configuration*/
        SPI_InitStruct.TransferDirection = LL_SPI_HALF_DUPLEX_TX; //LL_SPI_FULL_DUPLEX;
        SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
        SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
        SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
        SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
        SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
        SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV64;
        SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
        SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
        SPI_InitStruct.CRCPoly = 7;
  
        LL_SPI_Init(SPIx, &SPI_InitStruct);
        LL_SPI_SetStandard(SPIx, LL_SPI_PROTOCOL_MOTOROLA);
        // LL_SPI_EnableNSSPulseMgt(SPIx);
        LL_SPI_DisableNSSPulseMgt(SPIx);

        LL_SPI_EnableDMAReq_TX(SPIx);
        LL_SPI_Enable(SPIx);
    }

    void boot(SerialDevice_SPI&  serial, 
              SPIDevID spi_id, 
              bte::ISystemClock& clock,
              int buffer_elements,
              uint32_t *dma_buffer)
    {
        serial.set_spi(spi_id);
        serial.set_clock(clock);
        serial.buffer_elements = buffer_elements;
        serial.dma_buffer = dma_buffer;
        for(int i=0;i<buffer_elements;i++) dma_buffer[i] = 0;

        boot_spi1_pa1_pa7(spi::get(serial.get_spi()), dma_buffer, buffer_elements*sizeof(uint32_t));
    }
}  // namespace stm32g0xx

