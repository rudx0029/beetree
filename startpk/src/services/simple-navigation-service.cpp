//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/services/simple-navigation-service.hpp"
#include "beetree/units/methods.hpp"

namespace bte {
using namespace units::literals;
using PublicModel   = SimpleNavigationService::PublicModel;
using InternalModel = SimpleNavigationService::InternalModel;
using Angle         = units::Angle;
using Coordinate    = units::Coordinate;
using Length        = units::Length;

SimpleNavigationService::SimpleNavigationService(PublicModel& model, InternalModel& internal_model)
    : m_model(&model), m_internal_model(&internal_model)
{}

void SimpleNavigationService::configure(IMotionService&                       motion_svc,
                                        const SimpleGoToPositionTask::Config& goto_config,
                                        const SimpleRotateTask::Config&       rotate_config)
{
    m_goto_pos_task.configure(motion_svc, *m_model, goto_config);
    m_rotate_task.configure(motion_svc, *m_model, rotate_config);
};

const PublicModel& SimpleNavigationService::model() const { return *m_model; }

Task SimpleNavigationService::rotate_to(Angle heading, Clock::ms timeout)
{
    m_rotate_task.initialize(heading);
    return {m_rotate_task, timeout};
}

Task SimpleNavigationService::go_to(const Coordinate& pos, Clock::ms timeout)
{
    m_goto_pos_task.initialize(pos);
    return {m_goto_pos_task, timeout};
}

void SimpleNavigationService::null_odometry()
{
    m_model->measured_pose = {0_m, 0_m, 0_rad};

    m_internal_model->is_null_odometry_signaled = true;
}
}  // namespace bte