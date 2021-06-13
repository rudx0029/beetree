#pragma once

#include "beetree/controllers/pid.hpp"
#include "beetree/units/motion-profile.hpp"
#include "beetree/units/pose-2d.hpp"

namespace bte {
class GoalController
{
public:
    void reset(const units::Pose2D& target, const units::Pose2D& current);
    void configure(const PID::Config& pid,
                   units::Length      threshold_dist,
                   units::Velocity    travel_vel);

    units::MotionProfile step(const units::Pose2D& target,
                              const units::Pose2D& current,
                              units::Length*       distance_from_target = nullptr);

private:
    units::Length   m_threshold_dist;
    units::Velocity m_travel_vel;
    units::Length   m_init_dist;

    PID m_pid;
};
}  // namespace bte
