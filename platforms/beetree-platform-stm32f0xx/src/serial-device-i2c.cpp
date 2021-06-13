///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "beetree/platform/stm32f0xx/serial-device-i2c.hpp"
#include "beetree/platform/stm32f0xx/helpers.hpp"
#include "beetree/platform/stm32f0xx/hal/stm32f0xx_ll_i2c.h"


namespace stm32f0xx
{
    int32_t SerialDevice_I2C::write(std::size_t address,
                                    const uint8_t* data,
                                    std::size_t len,
                                    bte::chrono::duration_ms timeout)
    {
        bool fail = false;
        int tx_bytes = 0;
        do
        {
            I2C_TypeDef* I2Cx = i2c::get(get_i2c());
            
            bte::chrono::timepoint_ms start = m_clock->now_ms();
            
            //
            // data format [0] is the register
            //             [1..n] is the data to be written
            //
            int idx = 0;
            int tmpLen = len + 1;

            LL_I2C_SetSlaveAddr(I2Cx, (address<<1)); /* Prepare Address to send */
            LL_I2C_SetMasterAddressingMode(I2Cx, LL_I2C_ADDRSLAVE_7BIT);
            LL_I2C_SetTransferRequest(I2Cx, LL_I2C_REQUEST_WRITE); /* Reguest write */

            LL_I2C_SetTransferSize(I2Cx, tmpLen); /* Set transfer size register */

            LL_I2C_GenerateStartCondition(I2Cx); /* generate I2C Start address and send address*/
            while(READ_BIT(I2Cx->CR2, I2C_CR2_START))
            {
                if ((m_clock->now_ms() - start) > timeout) 
                {
                    fail = true;
                    break;
                }
            }
            if (fail) break;

            while (tmpLen--)
            {
                LL_I2C_TransmitData8(I2Cx, data[idx++]); 

                while(!LL_I2C_IsActiveFlag_TXE(I2Cx))
                {
                    if ((m_clock->now_ms() - start) > timeout) 
                    {
                        fail = true;
                        break;
                    }
                }
                if (fail) break;

                tx_bytes++;
            }

            LL_I2C_GenerateStopCondition(I2Cx);
            while(READ_BIT(I2Cx->CR2, I2C_CR2_STOP))
            {
                if ((m_clock->now_ms() - start) > timeout) 
                {
                    //
                    // Let this die without error.
                    //
                    break;
                }
            }

        } while (false);
        
        if (fail)
            tx_bytes = 0;

        return tx_bytes;
    }
 
    int32_t SerialDevice_I2C::read(std::size_t address,
                                    uint8_t* data,
                                    std::size_t len,
                                    bte::chrono::duration_ms timeout)
    {
        bool fail = false;
        int rx_bytes = 0;
        do
        {
            I2C_TypeDef* I2Cx = i2c::get(get_i2c());
            
            bte::chrono::timepoint_ms start = m_clock->now_ms();
            
            //
            // data format [0] is the register
            //             [0..n] is the data to be read
            // we will just overwrite the register with the data to be received
            //
            int idx = 0;

            //
            // First send the address and write.
            //
            LL_I2C_SetSlaveAddr(I2Cx, (address<<1)); /* Prepare Address to send */
            LL_I2C_SetMasterAddressingMode(I2Cx, LL_I2C_ADDRSLAVE_7BIT);

            LL_I2C_SetTransferRequest(I2Cx, LL_I2C_REQUEST_WRITE); /* Reguest write */
            LL_I2C_SetTransferSize(I2Cx, 1); /* Set transfer size register */

            LL_I2C_GenerateStartCondition(I2Cx); /* generate I2C Start address and send address*/
            while(READ_BIT(I2Cx->CR2, I2C_CR2_START))
            {
                if ((m_clock->now_ms() - start) > timeout) 
                {
                    fail = true;
                    break;
                }
            }
            if (fail) break;

            LL_I2C_TransmitData8(I2Cx, data[0]); /* send data out */

            while(!LL_I2C_IsActiveFlag_TXE(I2Cx))
            {
                if ((m_clock->now_ms() - start) > timeout) 
                {
                    fail = true;
                    break;
                }
            }
            if (fail) break;

            //
            // HOW DO I WAIT FOR AN ACK?
            //
            LL_I2C_SetTransferRequest(I2Cx, LL_I2C_REQUEST_READ); /* Reguest write */
            LL_I2C_SetTransferSize(I2Cx, len); /* Set transfer size register */

            LL_I2C_GenerateStartCondition(I2Cx); /* generate I2C Start address and send address*/
            while(READ_BIT(I2Cx->CR2, I2C_CR2_START))
            {
                if ((m_clock->now_ms() - start) > timeout) 
                {
                    fail = true;
                    break;
                }
            }
            if (fail) break;

            while (len--)
            {
                while(!LL_I2C_IsActiveFlag_RXNE(I2Cx))
                {
                    if ((m_clock->now_ms() - start) > timeout) 
                    {
                        fail = true;
                        break;
                    }
                }
                if (fail) break;

                data[idx++] = LL_I2C_ReceiveData8(I2Cx); /* get data */
                rx_bytes++;

                //
                // Send a NAK on the last byte.
                //
                if (len)
                    LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_ACK);
                else
                    LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_NACK);
            }

            LL_I2C_GenerateStopCondition(I2Cx);
            while(READ_BIT(I2Cx->CR2, I2C_CR2_STOP))
            {
                if ((m_clock->now_ms() - start) > timeout) 
                {
                    //
                    // Let this die without error.
                    //
                    break;
                }
            }

        } while (false);
        
        if (fail)
            rx_bytes = 0;

        return rx_bytes;
    }

}  // namespace stm32f0xx