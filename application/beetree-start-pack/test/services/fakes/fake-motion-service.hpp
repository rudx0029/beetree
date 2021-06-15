//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/services/i-motion-service.hpp"
#include "gmock/gmock.h"

namespace bte {
namespace test {
namespace internal {

class FakeMotionService : public IMotionService
{
public:
    // provide write access to the model in the unit test
    MotionModel fake_model;

    const MotionModel& model() const override;
    void               move(const units::MotionProfile& mp) override;
    void               stop() override;
};
}  // namespace internal
}  // namespace test
}  // namespace bte