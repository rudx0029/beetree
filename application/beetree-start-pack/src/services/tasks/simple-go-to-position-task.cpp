//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/services/tasks/simple-go-to-position-task.hpp"
#include "beetree/units/methods.hpp"

namespace bte {
using units::Angle;
using units::atan2;
using units::Coordinate;
using units::cos;
using units::Length;
using units::MotionProfile;
using units::sin;

void SimpleGoToPositionTask::configure(IMotionService&  motion_svc,
                                       NavigationModel& nav_model,
                                       const Config&    cfg)
{
    m_motion_svc       = &motion_svc;
    m_nav_model        = &nav_model;
    m_at_pos_threshold = cfg.at_pos_threshold;
    m_ctrl.configure(cfg.goal_pid_config, cfg.near_pos_threshold, cfg.travel_velocity);
}

void SimpleGoToPositionTask::initialize(const units::Coordinate& target)
{
    auto& commanded_pose = m_nav_model->commanded_pose;
    auto& measured_pose  = m_nav_model->measured_pose;

    // issue a new command pose
    commanded_pose = units::to_pose(target);

    // calculate the heading
    Length dx              = commanded_pose.x - measured_pose.x;
    Length dy              = commanded_pose.y - measured_pose.y;
    commanded_pose.heading = units::atan2(dy, dx);

    // reset the PID controller to reflect the new settings
    m_ctrl.reset(commanded_pose, measured_pose);
}

bool SimpleGoToPositionTask::run()
{
    auto&  commanded_pose = m_nav_model->commanded_pose;
    auto&  measured_pose  = m_nav_model->measured_pose;
    Length distance_from_target;

    MotionProfile mp = m_ctrl.step(commanded_pose, measured_pose, &distance_from_target);

    bool keep_running = distance_from_target > m_at_pos_threshold;
    if (keep_running)
    {
        m_motion_svc->move(mp);
    }

    return keep_running;
}
}  // namespace bte