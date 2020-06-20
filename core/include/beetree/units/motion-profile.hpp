//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/units/units.hpp"

namespace bte {
namespace units {

namespace {
using namespace literals;
}

struct MotionProfile
{
    Velocity    velocity        = 0_mps;
    Accel       acceleration    = 0_mpss;
    AngVelocity angularVelocity = 0_radps;

    constexpr MotionProfile() = default;
    constexpr MotionProfile(const Velocity& v, const Accel& a, const AngVelocity& w)
        : velocity(v), acceleration(a), angularVelocity(w)
    {}
};
}  // namespace units
}  // namespace bte