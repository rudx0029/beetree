//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/platform/stm32f0xx/pwm.hpp"
#include "hal/stm32f0xx_ll_tim.h"

namespace stm32f0xx {

/* TIM3 init function */
namespace tim3 {

void PwmOnPb0::write(uint32_t value) { LL_TIM_OC_SetCompareCH3(TIM3, value); }
void PwmOnPb1::write(uint32_t value) { LL_TIM_OC_SetCompareCH4(TIM3, value); }

}  // namespace tim3
}  // namespace stm32f0xx