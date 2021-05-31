//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/platform/stm32g0xx/pwm.hpp"
#include "hal/stm32g0xx_ll_tim.h"

namespace stm32g0xx {

namespace tim16 {
void PwmOnPa6::write(uint32_t value) { LL_TIM_OC_SetCompareCH1(TIM16, value); }
}
namespace tim14 {
void PwmOnPa7::write(uint32_t value) { LL_TIM_OC_SetCompareCH1(TIM14, value); }
}  // namespace tim3
}  // namespace stm32f0xx