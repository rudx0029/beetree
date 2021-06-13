//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/platform/stm32g0xx/bno055-imu-device.hpp"

namespace stm32g0xx {

//
// bno055 table driver - see datasheet BST_BNO055_DS000_12.pdf 
// (https://cdn-shop.adafruit.com/datasheets/BST_BNO055_DS000_12.pdf)
//
constexpr DevTable imu_init_table[] = 
{
    {opSleep,   0,      0,      100},   // 1 seconds startup. - POR time page 13.
    {opTest,    0,      0xA0,   10},    // REG 0 - CHIP ID - Read the chip version and stay here until it reads back correctly or 10 times.
    {opSleep,   0,      0,      1},     // skip one
    {opWrite,   0x3F,   0x01,   1},     // REG 3F - INITIATE Self Test (ST)
    {opSleep,   0,      0,      100},    // wait 50 cycles for self test
    {opTest,    0x36,   0x0F,   100},    // REG 36 - read back F when selftest complete. Fail if not done in 50 cycles.

    {opWrite,   0x3D,   0,      1},     // REG 3D - 0 sets OP mode to CONFIG mode - page 20 
    {opSleep,   0,      0,      50},    // skip 50 - time to enter config mode is 
    {opWrite,   0x3F,   0x20,   1},     // REG 3F - 20 resets the chip.
    {opSleep,   0,      0,      100},    // skip 50 - POR time 
    {opTest,    0,      0xA0,   50},    // REG 0 CHIP ID - wait for the chip to come back.
    {opSleep,   0,      0,      4},     // skip 4
    {opWrite,   0x3E,   0,      1},     // REG 3E - power mode to normal power mode
    {opSleep,   0,      0,      10},    // skip ten
    {opWrite,   0x07,   0,      1},     // REG 7 - 0 selects page 0
    {opSleep,   0,      0,      10},    // skip ten
    {opWrite,   0x3F,   0,      1},     // REG 3F - clear the trigger bit.
    {opSleep,   0,      0,      50},    // skip fifty

    {opWrite,   0x41,   0x21,   1},     // axis config - page 25
    {opSleep,   0,      0,      2},     // skip 2
    {opWrite,   0x42,   0x2,    1},     // axis sign
    {opSleep,   0,      0,      2},     // skip 2

    {opWrite,   0x3B,   0x80,   1},     // set units to Euler - page 30
    {opSleep,   0,      0,      2},     // skip two

    {opWrite,   0x3D,   0x8,    1},     // REG 3D - IMU mode
    {opSleep,   0,      0,      50},    // skip 50 for mode change to take effect
    {opEnd,     0,      0,      0}    
};

constexpr DevTable imu_health_table[] = 
{
    {opSleep,   0,      0,      10},
    {opTest,    0x36,   0xF,    10},    // REG 36 - confirm all ST succeeded 
    {opTest,    0x35,   0x30,   100},   // REG 35 - confirm gyro calibration 
    // Add to this a check for calibration
    {opEnd,     0,      0,      0}    
};

//
// TODO: need to add roll and pitch to yaw (heading) when we go 3d
//
constexpr DevTable imu_heading_table[] = 
{
    {opSleep,   0,      0,      20},
    {opRead16,  0x1A,   0,      10},    // REG 1A:1B - heading.
    {opEnd,     0,      0,      0}    
};

//
// Used to make sure the device is setup properly
//
// If anything fails in the process it starts over from the top of the table
// when it successfully gets thru the table it continues.
//
bool IMUDeviceBNO055::init_dev()
{
    return table(imu_init_table);
}

//
// Used to make sure the device is healthy and useable.
//
// Like init, it will cycle until it gets calibrated and is healthy.
//
bool IMUDeviceBNO055::health_dev()
{
    return table(imu_health_table);
}

//
// returns the relative heading from IMU mode
//
bool IMUDeviceBNO055::application_dev()
{
    return table(imu_heading_table);
}

//
// need to know when its okay to report heading back.
//
bool IMUDeviceBNO055::ready_imu()
{
    //
    // This doesn't work for more than one client.
    //
    bool ret = m_initialized && m_healthy && m_have_data;
    m_have_data = false;

    return ret;

}

void IMUDeviceBNO055::reset_imu()
{
    m_initialized = false;
    m_healthy = false;
    m_have_data = false;
}

//
// run from the sense scan
// Bring up the chip
// Checks health
// Gets heading
//
void IMUDeviceBNO055::sense_imu()
{
    if (m_initialized)
    {
        if (m_healthy)
        {
            //
            // Returns true when its gotten to the end of its table with a result.
            //
            if (application_dev())
            {
                //
                // Need to send a signal here that we have new data
                //
                m_have_data = true;
                m_theta = read();
            }
        }
        else
        {
            //
            // Returns true when its successfully finishes its table
            //
            if (health_dev())
            {
                m_healthy = true;
            }
        }
    }
    else
    {
        //
        // Returns true when it successfully finishes its table
        //
        if (init_dev())
        {
            m_initialized = true;
        }
    }
}

namespace bno055
{
uint32_t bno055AnalogInput::read() 
{
    m_imu.sense_imu();

    //
    // get the latest heading.
    //
    return m_imu.read();
}
} // bno055

} // stm32f0xx