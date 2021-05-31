//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "platform-library/stm32f1xx/counter.hpp"
#include "platform-library/stm32f1xx/hal/stm32f1xx_ll_gpio.h"

// gdb
uint32_t lw = 0, rw = 0;

namespace stm32f1xx {
using bte::chrono;

namespace exti_line10 {

void CounterOnPd10::set(uint32_t value) { m_lw_ticks = value; }

uint32_t CounterOnPd10::read() { return m_lw_ticks; }

void CounterOnPd10::on_interrupt()
{
    chrono::timepoint_ms now = m_clock->now_ms();
    uint32_t             period;

    m_lw_ticks++;
    m_lw_ticks &= 32767;
    lw           = m_lw_ticks;
    period       = now - m_lw_last_ms;
    m_lw_last_ms = now;
    m_lw_recent_period_ms += period;
}
}  // namespace exti_line10

namespace exti_line11 {
void     CounterOnPd11::set(uint32_t value) { m_rw_ticks = value; }
uint32_t CounterOnPd11::read() { return m_rw_ticks; }

void CounterOnPd11::on_interrupt()
{
    chrono::timepoint_ms now = m_clock->now_ms();
    uint32_t             period;

    m_rw_ticks++;
    m_rw_ticks &= 32767;
    rw           = m_rw_ticks;
    period       = now - m_rw_last_ms;
    m_rw_last_ms = now;
    m_rw_recent_period_ms += period;
}

}  // namespace exti_line11

bool lb, rb;

namespace exti_line12 {
void CounterOnPc12::reset() { bump_left_ts = 0; }
bool CounterOnPc12::is_set(void)
{
    return lb = LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_12) ? true : false;
}
int32_t CounterOnPc12::read() { return bump_left_ts; }

void CounterOnPc12::on_interrupt()
{
    if (bump_left_ts == 0)
    {
        bump_left_ts = m_clock->now_ms();
    }
}

}  // namespace exti_line12

namespace exti_line0 {
void CounterOnPd0::reset() { bump_right_ts = 0; }
bool CounterOnPd0::is_set(void)
{
    return rb = LL_GPIO_IsInputPinSet(GPIOD, LL_GPIO_PIN_0) ? true : false;
}
int32_t CounterOnPd0::read() { return bump_right_ts; }

void CounterOnPd0::on_interrupt()
{
    if (bump_right_ts == 0)
    {
        bump_right_ts = m_clock->now_ms();
    }
}

}  // namespace exti_line0

}  // namespace stm32f1xx