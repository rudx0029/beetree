//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/models/navigation-model.hpp"
#include "beetree/services/core/task.hpp"
#include "beetree/units/coordinate.hpp"

namespace bte {
struct INavigationService
{
public:
    ///
    /// @return the navigation model
    ///
    virtual const NavigationModel& model() const = 0;
    ///
    /// Moves the robot from the current position to the given global or
    /// absolute position.
    ///
    /// @note
    /// use units::to_abs_coord to convert from a relative coordinate to a
    /// coordinate in the global frame.
    ///
    /// @param pos the global coordinate to move the robot to
    /// @param timeout maximum amount of time the task can run
    /// @return the Task handling the operation
    ///
    virtual Task go_to(const units::Coordinate& pos, Clock::ms timeout) = 0;
    ///
    /// Rotates the robot from its current heading to the specified heading.
    ///
    /// @note
    /// Use units::to_abs_heading to convert from a relative angle to a heading
    /// in the global frame
    ///
    /// @param heading the global heading to rotate to
    /// @param timeout maximum amount of time the task can run
    /// @return the Task handling the operation
    ///
    virtual Task rotate_to(units::Angle heading, Clock::ms timeout) = 0;
    ///
    /// Informs the platform to null its odometry, resetting it to 0.
    ///
    virtual void null_odometry() = 0;

    //-----------------------------------
    INavigationService()                          = default;
    virtual ~INavigationService()                 = default;
    INavigationService(const INavigationService&) = delete;
    INavigationService(INavigationService&&)      = delete;
    INavigationService& operator=(const INavigationService&) = delete;
    INavigationService& operator=(INavigationService&&) = delete;
};
}  // namespace bte