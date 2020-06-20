//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "../hal/stm32f1xx_ll_gpio.h"
#include "../hal/stm32f1xx_ll_tim.h"
#include "platform-library/stm32f1xx/boot.hpp"
#include "platform-library/stm32f1xx/helpers.hpp"

uint32_t t = 0;

namespace stm32f1xx {
namespace tim4 {
void boot_pwm_pd12_pd13(uint32_t autoreload, uint32_t prescaler)
{
    // > Initialize
    LL_TIM_InitTypeDef TIM_InitStruct;
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;
    LL_GPIO_InitTypeDef GPIO_InitStruct;

    TIM_InitStruct.Prescaler     = prescaler;
    TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload    = autoreload;  // autoreload is period
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_Init(TIM4, &TIM_InitStruct);

    LL_TIM_EnableARRPreload(TIM4);

    // > Dual Channel Configuration
    LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH1);

    TIM_OC_InitStruct.OCMode       = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState      = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState     = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = 0;
    TIM_OC_InitStruct.OCPolarity   = LL_TIM_OCPOLARITY_HIGH;
    LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

    LL_TIM_OC_DisableFast(TIM4, LL_TIM_CHANNEL_CH1);

    LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH2);

    TIM_OC_InitStruct.OCMode       = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState      = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState     = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = 0;
    TIM_OC_InitStruct.OCPolarity   = LL_TIM_OCPOLARITY_HIGH;
    LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);
    
    LL_TIM_OC_DisableFast(TIM4, LL_TIM_CHANNEL_CH2);

    // > Finalize
    LL_TIM_SetTriggerOutput(TIM4, LL_TIM_TRGO_RESET);

    LL_TIM_DisableMasterSlaveMode(TIM4);

    // > GPIO Configuration
    // TIM4 GPIO Configuration
    // PD12     ------> TIM4_CH1 --> LW
    // PD13     ------> TIM4_CH2 --> RW
    //

    // lw_pwm
    GPIO_InitStruct.Pin = gpio::get(GPIOPin::PD12).pin;
    GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(gpio::get(GPIOPin::PD12).port, &GPIO_InitStruct);

    // rw_pwm
    GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pin = gpio::get(GPIOPin::PD13).pin;
    LL_GPIO_Init(gpio::get(GPIOPin::PD13).port, &GPIO_InitStruct);

    LL_GPIO_AF_EnableRemap_TIM4();
    
    // > Start output signal generation
    // Enable output channels 1 & 2
    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2);

    // Enable counter
    LL_TIM_EnableCounter(TIM4);

    // Force update generation
    LL_TIM_EnableARRPreload(TIM4);
    LL_TIM_GenerateEvent_UPDATE(TIM4);

    t = LL_TIM_GetCounter(TIM4);

}
}  // namespace tim4
}  // namespace stm32f1xx