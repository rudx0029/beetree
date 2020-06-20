#pragma once

#include "beetree/facilities/facilities-defs.hpp"
#include "beetree/units/units.hpp"

namespace bte {

namespace {
using namespace units::literals;
}

///
/// Encoder Reading for NON-quadrature encoders.
///
///
struct EncoderReading
{
    ///
    /// Total or absolute encoder tick count.
    ///
    /// The tick will increment regardless of direction of travel, it will
    /// never decrement.
    ///
    /// For example:
    /// If the wheel ticks once in the forward direction and once in the
    /// reverse direction, the tick count will increase by 2 and not by 0.
    ///
    /// Why:
    /// This is to simplify the platform layer such that the platform is
    /// only reading the tick count from the register and performing no
    /// other logic.
    ///
    ///
    units::Scalar ticks = 0_scl;
    ///
    /// The current motion of the travel the motors are engaged in.
    ///
    /// Typically, a discrete output is controlling if the motor is engaged
    /// going forward or reverse. This discrete output can be used to
    /// determine the direction of the encoder.
    ///
    Direction direction = Direction::FORWARD;

    ///
    /// Construct a new Encoder Reading object
    ///
    EncoderReading() = default;

    ///
    /// Construct a new Encoder Reading object
    ///
    /// @param t encoder ticks
    /// @param d forward or reverse direction
    ///
    EncoderReading(units::Scalar t, Direction d) : ticks(t), direction(d) {}

    ///
    /// Construct a new Encoder Reading object using raw inputs
    ///
    /// @param t encoder ticks
    /// @param is_forward true to set the direction to Forward and false to
    /// set the direction to Reverse
    ///
    EncoderReading(uint32_t t, bool is_forward)
        : ticks(units::make<units::scl>(t)),
          direction(is_forward ? Direction::FORWARD : Direction::REVERSE)
    {}
};
}  // namespace bte