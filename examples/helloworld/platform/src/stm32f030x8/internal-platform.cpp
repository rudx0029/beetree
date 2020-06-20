//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "internal-platform.hpp"

//#include "platform-library/stm32f0xx/hal/stm32f0xx_ll_tim.h"

namespace helloworld {
InternalPlatform& InternalPlatform::instance()
{
    static InternalPlatform s_instance;
    return s_instance;
}

// > Clock
bte::ISystemClock& Platform::clock() { return InternalPlatform::instance().clock; }

// > Discrete Outputs
bte::IDiscreteOutput& Platform::led() { return InternalPlatform::instance().led; }
bte::IDiscreteOutput& Platform::debug() { return InternalPlatform::instance().debug; }

// > Discrete Inputs
bte::IDiscreteInput& Platform::user_btn() { return InternalPlatform::instance().user_btn; }

bte::ISerialDevice& Platform::vcp() { return InternalPlatform::instance().vcp; }
}  // namespace helloworld