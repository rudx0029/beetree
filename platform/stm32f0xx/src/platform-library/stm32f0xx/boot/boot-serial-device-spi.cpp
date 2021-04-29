
#include "../hal/stm32f0xx_ll_bus.h"
#include "../hal/stm32f0xx_ll_dma.h"
#include "../hal/stm32f0xx_ll_gpio.h"
#include "../hal/stm32f0xx_ll_spi.h"

#include "platform-library/stm32f0xx/boot.hpp"
#include "platform-library/stm32f0xx/discrete-input.hpp"
#include "platform-library/stm32f0xx/discrete-output.hpp"
#include "platform-library/stm32f0xx/helpers.hpp"
#include "platform-library/stm32f0xx/serial-device-spi.hpp"

namespace stm32f0xx {

    // buffer usage in application
    // uint32_t spi_buffer[NFM_DATA_BUFFER_SIZE] alignas(32);

    void boot_spi1_pa7_pb3(SPI_TypeDef* SPIx, uint32_t* image_buffer, int buffer_size)
    {
        LL_SPI_InitTypeDef SPI_InitStruct = {0};
        LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

        /**SPI1 GPIO Configuration
         PA7   ------> SPI1_MOSI
        PB3   ------> SPI1_SCK
        */
        GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
        GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
        LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
        GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
        LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
        LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PRIORITY_LOW);
        LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_CIRCULAR); //LL_DMA_MODE_CIRCULAR); LL_DMA_MODE_NORMAL
        LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PERIPH_NOINCREMENT);
        LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_INCREMENT);
        LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PDATAALIGN_BYTE);
        LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_BYTE);
     
        LL_DMA_SetDataLength(DMA1,LL_DMA_CHANNEL_2,  buffer_size);
        LL_DMA_SetPeriphAddress(DMA1,LL_DMA_CHANNEL_2, LL_SPI_DMA_GetRegAddr(SPIx));
        LL_DMA_SetMemoryAddress(DMA1,LL_DMA_CHANNEL_2,(uint32_t)&image_buffer[0]);

        /* SPI1 parameter configuration*/
        SPI_InitStruct.TransferDirection = LL_SPI_SIMPLEX_RX;
        SPI_InitStruct.Mode = LL_SPI_MODE_SLAVE;
        SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
        SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
        SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
        SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
        SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
        SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
        SPI_InitStruct.CRCPoly = 7;

        LL_SPI_Init(SPIx, &SPI_InitStruct);
        LL_SPI_SetStandard(SPIx, LL_SPI_PROTOCOL_MOTOROLA);
        LL_SPI_DisableNSSPulseMgt(SPIx);
        LL_DMA_DisableIT_TE(DMA1, LL_DMA_CHANNEL_2);

        LL_SPI_EnableDMAReq_RX(SPIx);
        LL_SPI_Enable(SPIx);
    }

    void start_transfer(SPI_TypeDef* spi);

    void boot(SerialDevice_SPI_S&  serial, 
              SPIDevID spi_id, 
              bte::ISystemClock& clock,
              int buffer_elements,
              uint32_t *dma_buffer,
              uint32_t *copy_buffer)
    {
        serial.set_spi(spi_id);
        serial.set_clock(clock);
        serial.buffer_elements = buffer_elements;
        serial.dma_buffer = dma_buffer;
        serial.copy_buffer = copy_buffer;
        for(int i=0;i<buffer_elements;i++) dma_buffer[i] = 0;

        boot_spi1_pa7_pb3(spi::get(serial.get_spi()), 
                        dma_buffer, 
                        buffer_elements*sizeof(uint32_t));

        serial.start_transfer(spi::get(serial.get_spi()));
    }
}  // namespace stm32f0xx

