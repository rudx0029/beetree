//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/platform/i-analog-output.hpp"

namespace stm32g0xx {
namespace tim14 {
class PwmOnPa7 : public bte::IAnalogOutput
{
public:
    void write(uint32_t value) override;    
};
}

namespace tim16 {
class PwmOnPa6 : public bte::IAnalogOutput
{
public:
    void write(uint32_t value) override;    
};
}

}  // namespace stm32g0xx