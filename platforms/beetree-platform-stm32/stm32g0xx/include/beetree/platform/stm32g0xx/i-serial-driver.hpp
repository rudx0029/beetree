//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <stdint.h>
#include "beetree/platform/stm32g0xx/serial-device-i2c.hpp"
#include "beetree/platform/stm32g0xx/discrete-output.hpp"

namespace stm32g0xx {

//
// This is a per driver context. 
// While the driver is used to interact with the table, 
// The context gives context for table management per device
//
struct ISerialDriverCtx
{
    int     c_idx;
    int     c_scan_count;
    int     c_error;
    uint8_t c_data[4];
    int32_t c_read;

    //
    // The serial device we are acting with
    //
    bte::ISerialDevice* c_dev;

    //
    // debug led
    //
    bte::IDiscreteOutput* led;

    //
    // The serial bus device's address
    //
    uint8_t c_address;

};

struct DevTable
{
    bool ( *devOp )(ISerialDriverCtx *, const DevTable *);
    uint8_t register_offset;
    uint8_t value;
    uint8_t scans;
};

//
// Declared here for convenience.
//
bool opIdle(ISerialDriverCtx *c, const DevTable *t);
bool opSleep(ISerialDriverCtx *c, const DevTable *t );
bool opWrite(ISerialDriverCtx *c, const DevTable *t );
bool opRead(ISerialDriverCtx *c, const DevTable *t);
bool opRead16(ISerialDriverCtx *c, const DevTable *t );
bool opTest(ISerialDriverCtx *c, const DevTable *t );
bool opTestInv(ISerialDriverCtx *c, const DevTable *t );
bool opEnd(ISerialDriverCtx *c, const DevTable *t );

//
// Base class for the serial driver.
// Configure and manage the serial driver with the SerialDriverCtx structure
//
class ISerialDriver
{
public:
    ISerialDriver() = default;
    virtual ~ISerialDriver() = default;
    
    //
    // This will run first - it brings up the chip in the scans
    //
    virtual bool init_dev() = 0;
    //
    // This will run in the scan to check the health. This is a loop table - 
    // When done, update the model and run the table again.
    //
    virtual bool health_dev() = 0;

    //
    // This will run in the scan to do the application. This is a loop table - 
    // When done, update the model and run the table again.
    //
    virtual bool application_dev() = 0;

    //
    // this is the common table driver.
    //
    bool table(const DevTable *t);

    //
    // this is getting the read data.
    //
    uint32_t read() { return m_ctx ? m_ctx->c_read : 0; }

protected:
    ISerialDriverCtx *m_ctx = nullptr;

};

}