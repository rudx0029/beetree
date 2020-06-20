//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "platform-library/stm32f1xx/pwm.hpp"
#include "hal/stm32f1xx_ll_tim.h"

uint32_t pwmlw = 0;
uint32_t pwmrw = 0;

namespace stm32f1xx {

/* TIM3 init function */
namespace tim4 {

//
// RW
//
void PwmOnPd13::write(uint32_t value) { pwmrw = value; LL_TIM_OC_SetCompareCH2(TIM4, value); }
//
// LW
//
void PwmOnPd12::write(uint32_t value) { pwmlw = value; LL_TIM_OC_SetCompareCH1(TIM4, value); }

}  // namespace tim4
}  // namespace stm32f1xx