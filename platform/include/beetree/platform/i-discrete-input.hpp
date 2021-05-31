///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file Discrete input interface
///-----------------------------------------------------------------------------

#pragma once

namespace bte {
///
/// Discrete Input Interface
///
/// Provides a common interface for accessing discrte input state.
///
class IDiscreteInput
{
public:
    IDiscreteInput()          = default;
    virtual ~IDiscreteInput() = default;

    ///
    /// Checks the state of the Discrete Input
    ///
    /// @return true if the discrete input's state represents a logical '1'
    /// @return false if the discrete input's state represents a logical '0'
    ///
    virtual bool is_set() const = 0;
};
}  // namespace bte