///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file Digital output interface
///-----------------------------------------------------------------------------

#pragma once

namespace bte {
///
/// Discrete Output Interface
///
/// Provides a common interface for accessing and modifying discrte output state.
///
class IDiscreteOutput
{
public:
    IDiscreteOutput()          = default;
    virtual ~IDiscreteOutput() = default;

    ///
    /// Sets the discrete output state to a logic '1'
    ///
    virtual void set() = 0;
    ///
    /// Clears the discrete output state to a logic '0'
    ///
    virtual void clear() = 0;
    ///
    /// Checks the state of the discrete output
    ///
    /// @return true if the discrete output's state represents a logical '1'
    /// @return false if the discrete output's state represents a logical '0'
    ///
    virtual bool is_set() const = 0;
    ///
    /// Toggles the discrete output's state.
    ///
    virtual void toggle() = 0;
};
}  // namespace bte