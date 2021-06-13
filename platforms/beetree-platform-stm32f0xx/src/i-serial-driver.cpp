//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/platform/stm32f0xx/i-serial-driver.hpp"

namespace stm32f0xx {

//
// For now an easy debug - maybe move it to context at a later date.
//
uint32_t _idle = 0;
uint32_t _read = 0;
uint32_t _write = 0;
uint32_t _test = 0;
uint32_t _sleep = 0;
uint32_t _end = 0;
uint8_t _data = 0;
int32_t _data16 = 0;
uint32_t _error = 0;

//
// table
//
// This is the main table driver.
//
bool ISerialDriver::table(const DevTable *t)
{
    bool end = false;
    
    if (t && m_ctx)
    {
        if (t[m_ctx->c_idx].devOp != nullptr)
        {
            end = (* t[m_ctx->c_idx].devOp)(m_ctx, t);
            m_ctx->c_scan_count++;
        }
        else
        {
            //
            // If someone plants a nullptr into the table,
            // treat it as an idle - if that was supposed to be an end.. bam.
            // OR i could reset the context and start over so this forces a loop.
            // OR is could end it at the nullptr...
            // let's see the idle way first.
            //
            m_ctx->c_idx++;
        }
        
    }
    _error = m_ctx->c_error;
    return end;
}

//
// devOps are not contained in the table or driver object and are independent.
// This gives us flexability in the development of a table
//

//
// opEnd
//
// This is th last operation of a table and returns true to the client.
// Housekeeping is to reset state such that it starts at the top of the table again.
// 
bool opEnd(ISerialDriverCtx *c, const DevTable *t)
{
    (void )t;

    _end++;
    c->c_idx = 0;
    c->c_scan_count = 0;
    c->led->clear();

    return true;
}

//
// opIdle
//
// This runs once and cleans up state
//
bool opIdle(ISerialDriverCtx *c, const DevTable *t)
{
    (void )t;

    c->c_idx++;
    c->c_scan_count = 0;
    _idle++;
    return false;    
}

//
// opSleep
//
// This runs scan_count times and when moves to the next
//
bool opSleep(ISerialDriverCtx *c, const DevTable *t)
{
    _sleep++;
    if (c->c_scan_count > t[c->c_idx].scans)
    {
        c->c_idx++;
        c->led->clear();
    }
    else
    {
        c->led->toggle();
    }
    
    return false;
}

//
// opWrite
//
// writes "value" to "register_offset"  - 8 bits
//
bool opWrite(ISerialDriverCtx *c, const DevTable *t)
{
    int32_t tmp;

    c->c_data[0] = t[c->c_idx].register_offset;
    c->c_data[1] = t[c->c_idx].value;
    tmp = c->c_dev->write(c->c_address, &c->c_data[0], 1, 4);
    if (tmp == 0)
    {
        c->c_error++;
        c->led->clear();
    }
    else
    {
        _write++;
        c->led->clear();
    }
    c->c_idx++;
    c->c_scan_count = 0;
    return false;
}

//
// opRead
//
// reads "register_offset" into context "read" - 8 bits
//
bool opRead(ISerialDriverCtx *c, const DevTable *t)
{
    int32_t tmp;

    c->c_data[0] = t[c->c_idx].register_offset;
    tmp = c->c_dev->read(c->c_address, &c->c_data[0], 1, 4);
    if (tmp == 0)
    {
        c->c_error++;
        c->led->clear();
    }
    else
    {
        _read++;
        c->led->clear();
    }            
    c->c_idx++;
    c->c_scan_count = 0;
    _data = c->c_read = c->c_data[0];
    return false;
}

//
// opRead16
//
// reads "register_offset" into context "read" - 16 bits
//
bool opRead16(ISerialDriverCtx *c, const DevTable *t)
{
    int32_t tmp;

    c->c_data[0] = t[c->c_idx].register_offset;
    tmp = c->c_dev->read(c->c_address, &c->c_data[0], 2, 4);
    if (tmp == 0)
    {
        c->c_error++;
    }
    else
    {
        _read++;
    }            
    c->c_idx++;
    c->c_scan_count = 0;
    _data16 = c->c_read = int32_t(c->c_data[1] << 8 | c->c_data[0]);
    return false;
}

//
// opTest
//
// reads from "register_offset" then ANDs result with "value".
// if that (and) operation results in "value" then go to next.
// if we exceed scan_count times we reset context state to restart top of table.
//
bool opTest(ISerialDriverCtx *c, const DevTable *t)
{
    int32_t tmp;

    c->c_data[0] = t[c->c_idx].register_offset;
    tmp = c->c_dev->read(c->c_address, &c->c_data[0], 1, 2);
    if (tmp == 0)
    {
        //
        // Its an error so reset to the top of the table.
        //
        c->c_idx = 0;
        c->c_scan_count = 0;
        c->c_error++;
        c->led->clear();
    }
    //
    // The mask is an AND - our comparision must produce equality
    //
    if ((c->c_data[0] & t[c->c_idx].value) == t[c->c_idx].value)
    {
        c->c_idx++;
        c->c_scan_count = 0;
        _test++;
        c->led->clear();
    }
    else if (c->c_scan_count > t[c->c_idx].scans)
    {
        //
        // On a timeout just try again.
        //
        c->c_idx = 0;
        c->c_scan_count = 0;
        c->c_error++;
        c->led->clear();
    }
    else
    {
        c->led->toggle();
    }
    
    return false;
}

//
// opTestInv
//
// reads from "register_offset" then ANDs result with "value".
// if that (and) operation results in 0 then go to next.
// opposed to opTest which is looking for the mask, we want to see all the bits
// go away in this operation. 
// if we exceed scan_count times we reset context state to restart top of table.
//
bool opTestInv(ISerialDriverCtx *c, const DevTable *t)
{
    int32_t tmp;

    c->c_data[0] = t[c->c_idx].register_offset;
    tmp = c->c_dev->read(c->c_address, &c->c_data[0], 1, 2);
    if (tmp == 0)
    {
        //
        // Its an error so reset to the top of the table.
        //
        c->c_idx = 0;
        c->c_scan_count = 0;
        c->c_error++;
        c->led->clear();
    }
    //
    // The mask is an AND - our comparision must produce equality
    //
    if ((c->c_data[0] & t[c->c_idx].value) == 0)
    {
        c->c_idx++;
        c->c_scan_count = 0;
        _test++;
        c->led->clear();
    }
    else if (c->c_scan_count > t[c->c_idx].scans)
    {
        //
        // On a timeout just try again.
        //
        c->c_idx = 0;
        c->c_scan_count = 0;
        c->c_error++;
        c->led->clear();
    }
    else
    {
        c->led->toggle();
    }
    
    return false;
}

}