///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/platform/i-analog-output.hpp"

namespace stm32f0xx {
class AnalogOutput : public bte::IAnalogOutput
{
public:
    AnalogOutput() = default;

    // > Interface

    void write(uint32_t) override {}
};
}  // namespace stm32f0xx