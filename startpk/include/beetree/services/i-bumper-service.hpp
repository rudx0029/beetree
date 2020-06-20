//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/models/data/bump.hpp"
#include "beetree/models/data/reflex.hpp"

namespace bte {
class IBumpService
{
public:
    using BumpIterator = const Bump*;

    //----------------
    // Present (Real Time)
    //----------------

    ///
    /// Gets the reflex id tied to the bump service.
    ///
    /// @return models::Reflex
    ///
    virtual Reflex get_reflex() const = 0;

    ///
    /// @return true when the robot is actively bumping something
    /// @return false otherwise
    ///
    virtual bool is_bumping() const = 0;

    ///
    /// @return Angle of incidence of the current bump
    /// This is CCW with respect to the forward facing robot or what angle on
    /// the robot was bumped CCW.
    ///
    virtual units::Angle bump_incidence() const = 0;

    ///
    /// Save a bump to the bump history
    ///
    /// @param position the position of the robot at the time of the bump
    /// @param incidence the angle of incidence of the bump
    ///
    virtual void record_bump(const units::Pose2D& position, units::Angle incidence) = 0;

    ///
    /// An iterator to the first bump recorded in history
    ///
    virtual BumpIterator begin() const = 0;
    ///
    /// An iterator indicating the end of the bump history
    ///
    virtual BumpIterator end() const = 0;
    ///
    /// Clears the bump history;
    ///
    virtual void clear_history() = 0;

    //-----------------------------------
    IBumpService()                    = default;
    virtual ~IBumpService()           = default;
    IBumpService(const IBumpService&) = delete;
    IBumpService(IBumpService&&)      = delete;
    IBumpService& operator=(const IBumpService&) = delete;
    IBumpService& operator=(IBumpService&&) = delete;
};
}  // namespace bte