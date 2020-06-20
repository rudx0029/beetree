//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/controllers/goal-controller.hpp"
#include "beetree/units/methods.hpp"

namespace bte {
using namespace units;
using namespace units::literals;

void GoalController::reset(const Pose2D& target, const Pose2D& current)
{
    m_pid.reset();
    m_init_dist = units::distance(to_coord(target), to_coord(current));
}

void GoalController::configure(const PID::Config& pid_cfg,
                               units::Length      threshold_dist,
                               units::Velocity    travel_vel)
{
    m_threshold_dist = threshold_dist;
    m_travel_vel     = travel_vel;
    m_pid.configure(pid_cfg);
}

units::MotionProfile GoalController::step(const Pose2D& target,
                                          const Pose2D& current,
                                          Length*       distance_from_target)
{
    Length dx, dy;
    Length distance       = units::distance(to_coord(target), to_coord(current), &dx, &dy);
    Angle  target_heading = atan2(dy, dx);

    // control on the angular veocity
    AngVelocity w = 1_rps * m_pid.step(target_heading, current.heading);

    // set the velocity dependent on how near/far we are to target
    Velocity v = m_travel_vel;

    // if begining the destination, then start the velocity at 1/3 of the
    // requested, ramping to full velocity once we pass the threshold.
    if (abs(m_init_dist - distance) < m_threshold_dist)
    {
        v = (m_travel_vel / 3_scl) *
            (2_scl * abs(m_init_dist - distance) / m_threshold_dist + 1_scl);
    }

    // if near the goal, start ramping the velocity down.
    if (distance < m_threshold_dist)
    {
        v = m_travel_vel * (distance / m_threshold_dist);
    }

    if (distance_from_target)
    {
        *distance_from_target = distance;
    }

    return {v, 0_mpss /* no support for accel */, w};
}
}  // namespace bte