//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "../hal/stm32f0xx_ll_gpio.h"
#include "../hal/stm32f0xx_ll_tim.h"
#include "platform-library/stm32f0xx/boot.hpp"
#include "platform-library/stm32f0xx/helpers.hpp"

namespace stm32f0xx {
namespace tim15 {
void boot_counter_pb14(uint32_t autoreload, uint32_t prescaler)
{
    /* Peripheral clock enable */

    /**TIM15 GPIO Configuration
    PB14   ------> TIM15_CH1
    */

    LL_GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin        = gpio::get(GPIOPin::PB14).pin;
    GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull       = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate  = LL_GPIO_AF_1;
    LL_GPIO_Init(gpio::get(GPIOPin::PB14).port, &GPIO_InitStruct);

    LL_TIM_InitTypeDef TIM_InitStruct;
    TIM_InitStruct.Prescaler         = prescaler;
    TIM_InitStruct.CounterMode       = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload        = autoreload;
    TIM_InitStruct.ClockDivision     = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter = 0;
    LL_TIM_Init(TIM15, &TIM_InitStruct);
    LL_TIM_DisableARRPreload(TIM15);
    LL_TIM_SetTriggerInput(TIM15, LL_TIM_TS_TI1FP1);
    LL_TIM_SetClockSource(TIM15, LL_TIM_CLOCKSOURCE_EXT_MODE1);
    LL_TIM_IC_SetFilter(TIM15, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV32_N8);
    LL_TIM_IC_SetPolarity(TIM15, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_BOTHEDGE);
    LL_TIM_DisableIT_TRIG(TIM15);
    LL_TIM_DisableDMAReq_TRIG(TIM15);
    LL_TIM_SetTriggerOutput(TIM15, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM15);
    LL_TIM_EnableCounter(TIM15);
}
}  // namespace tim15

namespace tim1 {
void boot_counter_pa8(uint32_t autoreload, uint32_t prescaler)
{
    /**TIM1 GPIO Configuration
    PA8   ------> TIM1_CH1
    */
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin        = gpio::get(GPIOPin::PA8).pin;
    GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull       = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate  = LL_GPIO_AF_2;
    LL_GPIO_Init(gpio::get(GPIOPin::PA8).port, &GPIO_InitStruct);

    LL_TIM_InitTypeDef TIM_InitStruct;
    TIM_InitStruct.Prescaler         = prescaler;
    TIM_InitStruct.CounterMode       = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload        = autoreload;
    TIM_InitStruct.ClockDivision     = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter = 0;
    LL_TIM_Init(TIM1, &TIM_InitStruct);

    LL_TIM_DisableARRPreload(TIM1);
    LL_TIM_SetTriggerInput(TIM1, LL_TIM_TS_TI1FP1);
    LL_TIM_SetClockSource(TIM1, LL_TIM_CLOCKSOURCE_EXT_MODE1);
    LL_TIM_IC_SetFilter(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV32_N8);
    LL_TIM_IC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_BOTHEDGE);
    LL_TIM_DisableIT_TRIG(TIM1);
    LL_TIM_DisableDMAReq_TRIG(TIM1);
    LL_TIM_SetTriggerOutput(TIM1, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM1);

    LL_TIM_EnableCounter(TIM1);
}
}  // namespace tim1
}  // namespace stm32f0xx