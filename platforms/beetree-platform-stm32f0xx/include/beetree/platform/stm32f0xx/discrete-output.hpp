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
#include "beetree/platform/i-discrete-output.hpp"
#include "beetree/platform/stm32f0xx/gpio-pin.hpp"

namespace stm32f0xx {
///
/// functional access to discrete output peripherals
///
namespace discrete_output {
///
/// Set the discrete output state to a logic '1'
///
/// @param pin the GPIO pin
///
void set(GPIOPin pin);
///
/// Clears the discrete output state to a logic '0'
///
/// @param pin the GPIO pin
///
void clear(GPIOPin pin);
///
/// Toggles the discrete output's state.
///
/// @param pin the GPIO pin
///
void toggle(GPIOPin pin);
///
/// Checks the state of the GPIO output pin.
///
/// @param pin the GPIO pin
/// @return true if the pin's state represents a logical '1'
/// @return false if the pin's state represents a logical '0'
///
bool is_set(GPIOPin pin);
}  // namespace discrete_output

///
/// Implementing the `bte::IDiscreteOutput` interface, `DiscreteOutput`
/// provides an object representation of a GPIO output pin on stm32f0xx
/// hardware.
///
class DiscreteOutput : public bte::IDiscreteOutput
{
public:
    DiscreteOutput() = default;

    ///
    /// Invoked by `platform::boot`, associates this discrete output to its
    /// gpio pin
    ///
    /// @param pin the gpio pin
    ///
    void set_pin(GPIOPin pin) { m_pin = pin; }
    ///
    /// Sets the gpio pin state to a logic '1'
    ///
    void set() override { discrete_output::set(m_pin); }
    ///
    /// Clears the gpio pin state to a logic '0'
    ///
    void clear() override { discrete_output::clear(m_pin); }
    ///
    /// Checks the state of the gpio pin
    ///
    /// @return true if the gpio pin's state represents a logical '1'
    /// @return false if the gpio pin's state represents a logical '0'
    ///
    bool is_set() const override { return discrete_output::is_set(m_pin); }
    ///
    /// Toggles the gpio pin's state.
    ///
    void toggle() override { discrete_output::toggle(m_pin); }

private:
    GPIOPin m_pin;
};

///
/// Implementing the `bte::IDiscreteOutput` interface,
/// `DiscreteOutputInv` provides an **inverted** object representation of a
/// GPIO output pin on stm32f0xx hardware.
///
class DiscreteOutputInv : public bte::IDiscreteOutput
{
public:
    DiscreteOutputInv() = default;

    ///
    /// Invoked by `platform::boot`, associates this inverted discrete
    /// output to its gpio pin
    ///
    /// @param pin the gpio pin
    ///
    void set_pin(GPIOPin pin) { m_pin = pin; }
    ///
    /// Sets the gpio pin state to a logic '0'
    ///
    void set() override { discrete_output::clear(m_pin); }
    ///
    /// Clears the gpio pin state to a logic '1'
    ///
    void clear() override { discrete_output::set(m_pin); }
    ///
    /// Checks the state of the gpio pin
    ///
    /// @return true if the gpio pin's state represents a logical '0'
    /// @return false if the gpio pin's state represents a logical '1'
    ///
    bool is_set() const override { return !discrete_output::is_set(m_pin); }
    ///
    /// Toggles the gpio pin's state.
    ///
    void toggle() override { discrete_output::toggle(m_pin); }

private:
    GPIOPin m_pin;
};
}  // namespace stm32f0xx