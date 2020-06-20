//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/models/internal/simple-navigation-model.hpp"
#include "beetree/services/i-navigation-service.hpp"
#include "beetree/services/tasks/simple-go-to-position-task.hpp"
#include "beetree/services/tasks/simple-rotate-task.hpp"

namespace bte {
class SimpleNavigationService : public INavigationService
{
public:
    using PublicModel   = NavigationModel;
    using InternalModel = SimpleNavigationModel;

    SimpleNavigationService(PublicModel& model, InternalModel& internal_model);

    void configure(IMotionService&                       motion_svc,
                   const SimpleGoToPositionTask::Config& goto_config,
                   const SimpleRotateTask::Config&       rotate_config);

    const NavigationModel& model() const override;

    Task go_to(const units::Coordinate& pos, Clock::ms timeout) override;
    Task rotate_to(units::Angle heading, Clock::ms timeout) override;

    void null_odometry() override;

private:
    PublicModel*           m_model          = nullptr;
    InternalModel*         m_internal_model = nullptr;
    SimpleGoToPositionTask m_goto_pos_task;
    SimpleRotateTask       m_rotate_task;
    units::Pose2D          m_initial_pose;
    bool                   m_initial_pose_init;
};
}  // namespace bte