//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/models/motion-model.hpp"
#include "beetree/units/motion-profile.hpp"

namespace bte {
class IMotionService
{
public:
    ///
    /// @return the motion model
    ///
    virtual const MotionModel& model() const = 0;
    ///
    /// Commands the robot to move with the given motion profile, i.e.
    /// velocity, angular velocity, etc.
    ///
    /// @param mp the motion profile
    ///
    virtual void move(const units::MotionProfile& mp) = 0;
    ///
    /// Commands the robot to stop.
    ///
    virtual void stop() = 0;

    //-----------------------------------
    IMotionService()                      = default;
    virtual ~IMotionService()             = default;
    IMotionService(const IMotionService&) = delete;
    IMotionService(IMotionService&&)      = delete;
    IMotionService& operator=(const IMotionService&) = delete;
    IMotionService& operator=(IMotionService&&) = delete;
};
}  // namespace bte