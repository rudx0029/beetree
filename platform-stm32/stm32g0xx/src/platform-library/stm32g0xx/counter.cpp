//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/platform/stm32g0xx/counter.hpp"
#include "hal/stm32g0xx_ll_exti.h"
#include "hal/stm32g0xx_ll_gpio.h"
#include "hal/stm32g0xx_ll_tim.h"

// gdb
uint32_t lw = 0, rw = 0;

namespace stm32g0xx {

/* TIM3 init function */
namespace tim1 {

uint32_t CounterOnPa8::read()
{
    uint32_t ticks;
    ticks = LL_TIM_GetCounter(TIM1);
    return ticks;
}
}  // namespace tim1

namespace tim3 {
uint32_t CounterOnPb4::read()
{
    uint32_t ticks;
    ticks = LL_TIM_GetCounter(TIM3);
    return ticks;
}
}  // namespace tim1

bool lb, rb;

namespace exti_line1 {
void CounterOnPa1::reset() { bump_left_ts = 0; }
bool CounterOnPa1::is_set(void)
{
    return lb = LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_1) ? true : false;
}
int32_t CounterOnPa1::read() { return bump_left_ts; }

void CounterOnPa1::on_interrupt()
{
    if (LL_EXTI_IsActiveRisingFlag_0_31(LL_EXTI_LINE_1) != RESET)
    {
        LL_EXTI_ClearRisingFlag_0_31(LL_EXTI_LINE_1);

        if (bump_left_ts == 0)
        {
            bump_left_ts = m_clock->now_ms();
        }
    }
}

}  // namespace exti_line0

namespace exti_line2 {
void CounterOnPb2::reset() { bump_right_ts = 0; }
bool CounterOnPb2::is_set(void)
{
    return rb = LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_2) ? true : false;
}
int32_t CounterOnPb2::read() { return bump_right_ts; }
void    CounterOnPb2::on_interrupt()
{
    if (LL_EXTI_IsActiveRisingFlag_0_31(LL_EXTI_LINE_2) != RESET)
    {
        LL_EXTI_ClearRisingFlag_0_31(LL_EXTI_LINE_2);
        if (bump_right_ts == 0)
        {
            bump_right_ts = m_clock->now_ms();
        }
    }
}
}  // namespace exti_line2

}  // namespace stm32f0xx