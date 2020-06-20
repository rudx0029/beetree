//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/platform/i-analog-input.hpp"
#include "beetree/platform/i-discrete-input-ts.hpp"
#include "beetree/platform/i-system-clock.hpp"

namespace stm32f0xx {
///
/// Timer 1 Counters (Input Compare)
///
namespace tim1 {
///
/// Incremental counter on pin PA8
///
class CounterOnPa8 : public bte::IAnalogInput
{
public:
    uint32_t read() override;
};
}  // namespace tim1

///
/// Timer 15 Counters (Input Compare)
///
namespace tim15 {
///
/// Incremental counter on pin PB14
///
class CounterOnPb14 : public bte::IAnalogInput
{
public:
    uint32_t read() override;
};
}  // namespace tim15

//
// Alternatively we can use external interrupt pins to reduce the need for timer resources
//
namespace exti_line11 {
class CounterOnPc11 : public bte::IAnalogInput
{
public:
    uint32_t read() override;

    void set(uint32_t value);

    void on_interrupt();
    ///
    /// Invoked by `bte::boot()` to set the system clock
    ///
    /// @param clock the system clock
    ///
    void set_clock(bte::ISystemClock& clock) { m_clock = &clock; }

private:
    uint32_t           m_lw_ticks            = 0;
    uint32_t           m_lw_recent_period_ms = 0;
    uint32_t           m_lw_last_ms          = 0;
    bte::ISystemClock* m_clock;
};
}  // namespace exti_line11

namespace exti_line12 {
class CounterOnPc12 : public bte::IAnalogInput
{
public:
    uint32_t read() override;

    void set(uint32_t value);

    void on_interrupt();
    ///
    /// Invoked by `bte::boot()` to set the system clock
    ///
    /// @param clock the system clock
    ///
    void set_clock(bte::ISystemClock& clock) { m_clock = &clock; }

private:
    uint32_t           m_rw_ticks            = 0;
    uint32_t           m_rw_recent_period_ms = 0;
    uint32_t           m_rw_last_ms          = 0;
    bte::ISystemClock* m_clock;
};
}  // namespace exti_line12

//
// So this is a stretch maybe, but we are looking for a tick count from the bumper switches..
// when did this happen and that is what we are reading and setting.. its a match with this
// interface..
//
namespace exti_line0 {
class CounterOnPc0 : public bte::IDiscreteInputTs
{
public:
    int32_t read() override;
    void    reset(void) override;
    bool    is_set(void) override;

    void on_interrupt();

    ///
    /// Invoked by `bte::boot()` to set the system clock
    ///
    /// @param clock the system clock
    ///
    void set_clock(bte::ISystemClock& clock) { m_clock = &clock; }

private:
    volatile uint32_t  bump_left_ts;
    bte::ISystemClock* m_clock;
};
}  // namespace exti_line0

namespace exti_line1 {
class CounterOnPc1 : public bte::IDiscreteInputTs
{
public:
    int32_t read() override;
    void    reset(void) override;
    bool    is_set(void) override;

    void on_interrupt();
    ///
    /// Invoked by `bte::boot()` to set the system clock
    ///
    /// @param clock the system clock
    ///
    void set_clock(bte::ISystemClock& clock) { m_clock = &clock; }

private:
    volatile uint32_t  bump_right_ts;
    bte::ISystemClock* m_clock;
};
}  // namespace exti_line1
}  // namespace stm32f0xx