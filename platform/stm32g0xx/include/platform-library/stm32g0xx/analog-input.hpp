///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/platform/i-analog-input.hpp"

namespace stm32g0xx {
class AnalogInput : public bte::IAnalogInput
{
public:
    AnalogInput() = default;

    // > Interface

    uint32_t read() override { return 0; }
};
}  // namespace stm32g0xx