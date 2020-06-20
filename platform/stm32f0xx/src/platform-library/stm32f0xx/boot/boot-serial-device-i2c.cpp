
#include "../hal/stm32f0xx_ll_bus.h"
#include "../hal/stm32f0xx_ll_dma.h"
#include "../hal/stm32f0xx_ll_gpio.h"
#include "../hal/stm32f0xx_ll_i2c.h"

#include "platform-library/stm32f0xx/boot.hpp"
#include "platform-library/stm32f0xx/discrete-input.hpp"
#include "platform-library/stm32f0xx/discrete-output.hpp"
#include "platform-library/stm32f0xx/helpers.hpp"


namespace stm32f0xx {

    
    void boot_i2c2_pb10_pb11(I2C_TypeDef* I2Cx)
    {
        LL_I2C_InitTypeDef I2C_InitStruct = {0};

        LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

        /**
         PB10   ------> I2C2_SCL
         PB11   ------> I2C2_SDA 
        */
        GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
        GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
        LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
        GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
        GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
        GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
        GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
        LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);

        /** I2C Initialization 
         */
        LL_I2C_StructInit(&I2C_InitStruct);
        LL_I2C_DisableOwnAddress2(I2Cx);
        LL_I2C_DisableGeneralCall(I2Cx);
        I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
        I2C_InitStruct.Timing = 0x4021050D; //0x2010091A;
        I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
        I2C_InitStruct.DigitalFilter = 0;
        I2C_InitStruct.OwnAddress1 = 0;
        I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
        I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
        LL_I2C_Init(I2Cx, &I2C_InitStruct);
        // LL_I2C_EnableAutoEndMode(I2Cx);
        LL_I2C_SetOwnAddress2(I2Cx, 0, LL_I2C_OWNADDRESS2_NOMASK);
        LL_I2C_EnableClockStretching(I2Cx);
    }

    void boot(SerialDevice_I2C&  serial, 
              I2CDevID i2c_id, 
              bte::ISystemClock& clock)
    {
        // unsigned char imu_data[4];
        // int count;

        serial.set_i2c(i2c_id);
        serial.set_clock(clock);
        boot_i2c2_pb10_pb11(i2c::get(serial.get_i2c()));

        serial.set_CHIP_ID(0);
        serial.set_ACC_ID(0);
        serial.set_MAG_ID(0);
        serial.set_GYR_ID(0);
    }
}  // namespace stm32f0xx    

