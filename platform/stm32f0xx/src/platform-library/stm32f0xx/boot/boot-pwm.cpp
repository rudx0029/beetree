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
namespace tim3 {
void boot_pwm_pb0_pb1(uint32_t autoreload, uint32_t prescaler)
{
    // > Initialize
    LL_TIM_InitTypeDef TIM_InitStruct;
    TIM_InitStruct.Prescaler     = prescaler;
    TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload    = autoreload;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;

    LL_TIM_Init(TIM3, &TIM_InitStruct);
    LL_TIM_EnableARRPreload(TIM3);

    // > Dual Channel Configuration
    LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH3);
    LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH4);

    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;
    TIM_OC_InitStruct.OCMode       = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState      = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState     = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = 0;
    TIM_OC_InitStruct.OCPolarity   = LL_TIM_OCPOLARITY_HIGH;

    LL_TIM_OC_Init(TIM3, LL_TIM_CHANNEL_CH3, &TIM_OC_InitStruct);
    LL_TIM_OC_Init(TIM3, LL_TIM_CHANNEL_CH4, &TIM_OC_InitStruct);

    LL_TIM_OC_DisableFast(TIM3, LL_TIM_CHANNEL_CH3);
    LL_TIM_OC_DisableFast(TIM3, LL_TIM_CHANNEL_CH4);

    // > Finalize
    LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM3);

    // > GPIO Configuration
    // TIM3 GPIO Configuration
    // PB0     ------> TIM3_CH3
    // PB1     ------> TIM3_CH4
    //
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull       = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate  = LL_GPIO_AF_1;

    GPIO_InitStruct.Pin = gpio::get(GPIOPin::PB0).pin;
    LL_GPIO_Init(gpio::get(GPIOPin::PB0).port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = gpio::get(GPIOPin::PB1).pin;
    LL_GPIO_Init(gpio::get(GPIOPin::PB1).port, &GPIO_InitStruct);

    // > Start output signal generation
    // Enable output channels 3 & 4
    LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH3);
    LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH4);

    // Enable counter
    LL_TIM_EnableCounter(TIM3);

    // Force update generation
    LL_TIM_GenerateEvent_UPDATE(TIM3);
}
}  // namespace tim3
}  // namespace stm32f0xx