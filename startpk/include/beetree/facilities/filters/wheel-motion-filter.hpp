#pragma once

#include "beetree/btos/clock.hpp"
#include "beetree/facilities/pipes/motion-2d.hpp"
#include "beetree/facilities/pipes/wheel-motion.hpp"

namespace bte {
class WheelMotionFilter
{
public:
    WheelMotionFilter() = default;

    ///
    /// Configures the filter
    ///
    /// @param ts interval that filter executes at, should be the application tick interval
    /// @param wheel_base the robot's wheel base length
    ///
    void configure(Clock::milliseconds ts, units::Length wheel_base);

    Motion2D apply(const WheelMotion& input);
    void     reset();

private:
    units::AngAccel    calc_alpha(const WheelMotion& input);
    units::AngVelocity calc_omega(const WheelMotion& input);
    units::Angle       calc_theta(const WheelMotion& input,
                                  units::AngVelocity omega,
                                  units::Angle       theta_0);
    units::Position    calc_x(const WheelMotion& input,
                              units::Velocity    vel,
                              units::Angle       theta,
                              units::Position    x_0);
    units::Position    calc_y(const WheelMotion& input,
                              units::Velocity    vel,
                              units::Angle       theta,
                              units::Position    y_0);

    Clock::milliseconds m_ts;
    units::Length       m_wheel_base;
    units::Length       m_last_y;
    units::Length       m_last_x;
    units::Angle        m_last_theta;
};
}  // namespace bte