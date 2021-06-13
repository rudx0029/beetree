//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/platform/i-serial-device.hpp"
#include "beetree/platform/i-analog-input.hpp"
#include "beetree/platform/i-discrete-input.hpp"
#include "beetree/platform/i-discrete-output.hpp"
#include "i-serial-driver.hpp"

namespace stm32g0xx {

class IMUDeviceBNO055 : public ISerialDriver
{
public:

    IMUDeviceBNO055() = default;
    virtual ~IMUDeviceBNO055() = default;
    
    void init(bte::ISerialDevice& dev, bte::IDiscreteOutput& led, uint8_t address)
    {
        m_dev_ctx.c_address = address;
        m_dev_ctx.c_dev = &dev;
        m_dev_ctx.led = &led;

        m_dev_ctx.c_idx = 0;
        m_dev_ctx.c_scan_count = 0;
        m_dev_ctx.c_error = 0;

        //
        // m_ctx is in the base driver and we set it up here
        // for use in the static interface.
        //
        m_ctx = &m_dev_ctx;
        
        m_initialized = false;
        m_healthy = false;
        m_have_data = false;
    }

    bool init_dev() override;
    bool health_dev() override;
    bool application_dev() override;
    void sense_imu();
    bool ready_imu();
    void reset_imu();
    bool initialized_imu() { return m_initialized && m_healthy; }

    int32_t m_theta;

private:
    bool m_initialized;
    bool m_healthy;
    bool m_have_data;
    ISerialDriverCtx m_dev_ctx;
};

namespace bno055
{

///
/// 
///
class bno055AnalogInput : public bte::IAnalogInput
{
public:
    uint32_t read() override;

    //
    // Used to config the interface at boot.
    //
    void init(SerialDevice_I2C& s, DiscreteOutput& l, uint8_t a) { m_imu.init(s, l, a); }
    
    IMUDeviceBNO055& get_imu_device() {return m_imu; }

private:
    IMUDeviceBNO055 m_imu;
};
///
/// 
///
class bno055Ready : public bte::IDiscreteInput
{
public:
    bool is_set() const override { return m_imu->ready_imu(); }

    void init(IMUDeviceBNO055& m) { m_imu = &m; }   
private:
    IMUDeviceBNO055 *m_imu = nullptr;
};

class bno055Initialized: public bte::IDiscreteInput
{
public:
    bool is_set() const override { return m_imu->initialized_imu(); }

    void init(IMUDeviceBNO055& m) { m_imu = &m; }   
private:
    IMUDeviceBNO055 *m_imu = nullptr;
};

class bno055Reset: public bte::IDiscreteOutput
{
public:
    bool is_set() const override { return m_imu->initialized_imu(); }
    void set() override { m_imu->reset_imu(); }
    void clear() override {}
    void toggle() override {}
    void init(IMUDeviceBNO055& m) { m_imu = &m; }   
private:
    IMUDeviceBNO055 *m_imu = nullptr;
};

} // namespace bno055

}