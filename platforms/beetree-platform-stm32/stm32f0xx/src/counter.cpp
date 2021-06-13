//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/platform/stm32f0xx/counter.hpp"
#include "hal/stm32f0xx_ll_exti.h"
#include "hal/stm32f0xx_ll_gpio.h"
#include "hal/stm32f0xx_ll_tim.h"

// gdb
uint32_t lw = 0, rw = 0;

namespace stm32f0xx {

/* TIM3 init function */
namespace tim1 {

uint32_t CounterOnPa8::read()
{
    uint32_t ticks;
    ticks = LL_TIM_GetCounter(TIM1);
    return ticks;
}
}  // namespace tim1
namespace tim15 {
uint32_t CounterOnPb14::read()
{
    uint32_t ticks;
    ticks = LL_TIM_GetCounter(TIM15);
    return ticks;
}
}  // namespace tim15

///
/// NOTE NOTE NOTE NOTE NOTE NOTE NOTE
///
/// IF YOU ARE ON AN M0 CHIP RUNNING SLOW (48MHZ) THE INTERRUPTS CAN'T KEEP UP WITH WHEEL MOTION.
/// USE THE TIMERS INSTEAD - ABOVE...
///

namespace exti_line11 {

void CounterOnPc11::set(uint32_t value) { m_lw_ticks = value; }

uint32_t CounterOnPc11::read() { return m_lw_ticks; }

void CounterOnPc11::on_interrupt()
{
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
        //
        // RW ENCODER
        //
        bte::chrono::timepoint_ms now = m_clock->now_ms();
        uint32_t                  period;

        m_lw_ticks++;
        m_lw_ticks &= 32767;  // current encoder assumes we have a count up to 32768
        lw           = m_lw_ticks;
        period       = now - m_lw_last_ms;
        m_lw_last_ms = now;
        m_lw_recent_period_ms += period;
    }
}
}  // namespace exti_line11

namespace exti_line12 {

void     CounterOnPc12::set(uint32_t value) { m_rw_ticks = value; }
uint32_t CounterOnPc12::read() { return m_rw_ticks; }

void CounterOnPc12::on_interrupt()
{
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_12) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);

        bte::chrono::timepoint_ms now = m_clock->now_ms();
        uint32_t                  period;

        m_rw_ticks++;
        m_rw_ticks &= 32767;
        rw           = m_rw_ticks;
        period       = now - m_rw_last_ms;
        m_rw_last_ms = now;
        m_rw_recent_period_ms += period;
    }
}
}  // namespace exti_line12

bool lb, rb;

namespace exti_line0 {
void CounterOnPc0::reset() { bump_left_ts = 0; }
bool CounterOnPc0::is_set(void)
{
    return lb = LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_0) ? true : false;
}
int32_t CounterOnPc0::read() { return bump_left_ts; }

void CounterOnPc0::on_interrupt()
{
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);

        if (bump_left_ts == 0)
        {
            bump_left_ts = m_clock->now_ms();
        }
    }
}

}  // namespace exti_line0

namespace exti_line1 {
void CounterOnPc1::reset() { bump_right_ts = 0; }
bool CounterOnPc1::is_set(void)
{
    return rb = LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_1) ? true : false;
}
int32_t CounterOnPc1::read() { return bump_right_ts; }
void    CounterOnPc1::on_interrupt()
{
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1) != RESET)
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
        if (bump_right_ts == 0)
        {
            bump_right_ts = m_clock->now_ms();
        }
    }
}
}  // namespace exti_line1

}  // namespace stm32f0xx