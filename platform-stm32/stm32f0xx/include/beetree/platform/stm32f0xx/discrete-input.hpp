///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#pragma once

#include <utility>
#include "beetree/platform/i-discrete-input.hpp"
#include "beetree/platform/stm32f0xx/gpio-pin.hpp"

namespace stm32f0xx {
///
/// functional access to discrete input peripherals
///
namespace discrete_input {
///
/// Checks the state of the GPIO input pin.
///
/// @param pin the GPIO pin
/// @return true if the pin's state represents a logical '1'
/// @return false if the pin's state represents a logical '0'
///
bool is_set(GPIOPin pin);
}  // namespace discrete_input

///
/// The DiscreteInput provides an object representation of a discrete input
/// peripherals.
///
class DiscreteInput : public bte::IDiscreteInput
{
public:
    DiscreteInput() = default;

    // > Modifiers

    ///
    /// Invoked by `boot()`, sets the GPIO associated with this instance.
    ///
    /// @param pin the GPIO pin
    ///
    void set_pin(GPIOPin pin) { m_pin = pin; }

    // > Interface

    ///
    /// Checks the state of the Discrete Input
    ///
    /// @return true if the underlying gpio pin's state represents a logical
    /// '1'
    /// @return false if the underlying gpio pin's state represents a
    /// logical '0'
    ///
    bool is_set() const override { return discrete_input::is_set(m_pin); }

private:
    GPIOPin m_pin;
};

///
/// The DiscreteInputInv provides an object representation of a discrete
/// input peripherals. However this variant 'inverts' the logic, meaning if
/// the hardware detects a logical '1', then 'is_set()' returns false.
///
class DiscreteInputInv : public bte::IDiscreteInput
{
public:
    DiscreteInputInv() = default;

    // > Modifiers

    ///
    /// Invoked by `boot()`, sets the GPIO associated with this instance.
    ///
    /// @param pin the GPIO pin
    ///
    void set_pin(GPIOPin pin) { m_pin = pin; }

    // > Interface

    ///
    /// Checks the state of the Inverted Discrete Input
    ///
    /// @return true if the underlying gpio pin's state represents a logical
    /// '0'
    /// @return false if the underlying gpio pin's state represents a
    /// logical '1'
    ///
    bool is_set() const override { return !discrete_input::is_set(m_pin); }

private:
    GPIOPin m_pin;
};
}  // namespace stm32f0xx