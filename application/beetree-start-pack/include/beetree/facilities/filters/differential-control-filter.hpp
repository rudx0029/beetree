//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/facilities/pipes/differential-control-input.hpp"
#include "beetree/facilities/pipes/wheels-control-input.hpp"
#include "beetree/units/units.hpp"

namespace bte {

namespace {
using namespace bte::units::literals;
}

class DifferentialControlFilter
{
public:
    using Input  = DifferentialControlInput;
    using Output = WheelsControlInput;

    Output apply(Input input);

    void configure(units::Length wheel_base);

    DifferentialControlFilter() = default;

private:
    units::Length m_wheel_base = 1_um;
};
}  // namespace bte