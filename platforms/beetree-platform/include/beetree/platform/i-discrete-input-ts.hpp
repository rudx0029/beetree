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
/// discrete input with timestamp
///
class IDiscreteInputTs
{
public:
    IDiscreteInputTs()          = default;
    virtual ~IDiscreteInputTs() = default;

    ///
    /// Reads the current value of the analog input.
    ///
    /// @return the value of the analog input
    ///
    virtual int32_t read() = 0;
    ///
    /// @return reads the value at the bit
    ///
    virtual bool is_set() = 0;
    ///
    /// reset value to 0
    ///
    virtual void reset() = 0;
};
}  // namespace bte