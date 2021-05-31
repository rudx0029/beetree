//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "../hal/stm32g0xx_ll_gpio.h"
#include "../hal/stm32g0xx_ll_tim.h"
#include "beetree/platform/stm32g0xx/boot.hpp"
#include "beetree/platform/stm32g0xx/helpers.hpp"

namespace stm32g0xx {

namespace tim14 {
void boot_pwm_pa7(uint32_t autoreload, uint32_t prescaler)
{
    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Peripheral clock enable */

    TIM_InitStruct.Prescaler = prescaler;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = autoreload;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_Init(TIM14, &TIM_InitStruct);

    LL_TIM_DisableARRPreload(TIM14);
    LL_TIM_OC_EnablePreload(TIM14, LL_TIM_CHANNEL_CH1);
    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = 0;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    LL_TIM_OC_Init(TIM14, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

    LL_TIM_OC_DisableFast(TIM14, LL_TIM_CHANNEL_CH1);

    LL_TIM_SetTriggerOutput(TIM14, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM14);

    /**TIM14 GPIO Configuration    
    PA7     ------> TIM14_CH1 
    */
    GPIO_InitStruct.Pin = gpio::get(GPIOPin::PA7).pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
    LL_GPIO_Init(gpio::get(GPIOPin::PA7).port, &GPIO_InitStruct);

    LL_TIM_CC_EnableChannel(TIM14, LL_TIM_CHANNEL_CH1);

    // Enable counter
    LL_TIM_EnableCounter(TIM14);

    // Force update generation
    LL_TIM_GenerateEvent_UPDATE(TIM14);    

}
}

namespace tim16 {
/* TIM16 init function */
void boot_pwm_pa6(uint32_t autoreload, uint32_t prescaler)
{
    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
    LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Peripheral clock enable */

    TIM_InitStruct.Prescaler = prescaler;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = autoreload;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter = 0;
    LL_TIM_Init(TIM16, &TIM_InitStruct);
    LL_TIM_DisableARRPreload(TIM16);
    LL_TIM_OC_EnablePreload(TIM16, LL_TIM_CHANNEL_CH1);
    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = 0;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCNPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
    TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;

    LL_TIM_OC_Init(TIM16, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
    LL_TIM_OC_DisableFast(TIM16, LL_TIM_CHANNEL_CH1);
    TIM_BDTRInitStruct.OSSRState = LL_TIM_OSSR_DISABLE;
    TIM_BDTRInitStruct.OSSIState = LL_TIM_OSSI_DISABLE;
    TIM_BDTRInitStruct.LockLevel = LL_TIM_LOCKLEVEL_OFF;
    TIM_BDTRInitStruct.DeadTime = 0;
    TIM_BDTRInitStruct.BreakState = LL_TIM_BREAK_DISABLE;
    TIM_BDTRInitStruct.BreakPolarity = LL_TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStruct.BreakFilter = LL_TIM_BREAK_FILTER_FDIV1;
    TIM_BDTRInitStruct.AutomaticOutput = LL_TIM_AUTOMATICOUTPUT_ENABLE;
    LL_TIM_BDTR_Init(TIM16, &TIM_BDTRInitStruct);

    LL_TIM_SetTriggerOutput(TIM16, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM16);

    /**TIM16 GPIO Configuration    
    PA6     ------> TIM16_CH1 
    */
    GPIO_InitStruct.Pin = gpio::get(GPIOPin::PA6).pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
    LL_GPIO_Init(gpio::get(GPIOPin::PA6).port, &GPIO_InitStruct);

    LL_TIM_CC_EnableChannel(TIM16, LL_TIM_CHANNEL_CH1);

    // Enable counter
    LL_TIM_EnableCounter(TIM16);

    // Force update generation
    LL_TIM_GenerateEvent_UPDATE(TIM16);        
}
}

}  // namespace stm32g0xx