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

namespace stm32g0xx {
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

namespace tim3 {
///
/// Incremental counter on pin PA8
///
class CounterOnPb4 : public bte::IAnalogInput
{
public:
    uint32_t read() override;
};
}  

// namespace tim1

//
// So this is a stretch maybe, but we are looking for a tick count from the bumper switches..
// when did this happen and that is what we are reading and setting.. its a match with this
// interface..
//
namespace exti_line1 {
class CounterOnPa1 : public bte::IDiscreteInputTs
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

namespace exti_line2 {
class CounterOnPb2 : public bte::IDiscreteInputTs
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
}  // namespace exti_line2
}  // namespace stm32g0xx