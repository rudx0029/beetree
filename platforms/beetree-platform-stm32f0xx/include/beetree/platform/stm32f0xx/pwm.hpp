//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/platform/i-analog-output.hpp"

namespace stm32f0xx {
namespace tim3 {
class PwmOnPb0 : public bte::IAnalogOutput
{
public:
    void write(uint32_t value) override;
};

class PwmOnPb1 : public bte::IAnalogOutput
{
public:
    void write(uint32_t value) override;
};
}  // namespace tim3
}  // namespace stm32f0xx