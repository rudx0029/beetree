//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/platform/i-analog-output.hpp"

namespace stm32f1xx {
namespace tim4 {
class PwmOnPd13 : public bte::IAnalogOutput
{
public:
    void write(uint32_t value) override;
};

class PwmOnPd12 : public bte::IAnalogOutput
{
public:
    void write(uint32_t value) override;
};
}  // namespace tim4
}  // namespace stm32f1xx