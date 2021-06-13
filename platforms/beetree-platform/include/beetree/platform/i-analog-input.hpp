//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <cstdint>

namespace bte {
///
/// Analog Input Interface
///
/// Provides a common interface for accessing analog input state.
///
class IAnalogInput
{
public:
    IAnalogInput()          = default;
    virtual ~IAnalogInput() = default;

    ///
    /// Reads the current value of the analog input.
    ///
    /// @return the value of the analog input
    ///
    virtual uint32_t read() = 0;
};
}  // namespace bte