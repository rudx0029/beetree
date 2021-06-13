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
/// Analog Output Interface
///
/// Provides a common interface for writing to an analog output.
///
class IAnalogOutput
{
public:
    IAnalogOutput()          = default;
    virtual ~IAnalogOutput() = default;

    ///
    /// Writes the value to the analog output.
    ///
    /// @param value the value to write to the anlog output
    ///
    virtual void write(uint32_t value) = 0;
};
}  // namespace bte