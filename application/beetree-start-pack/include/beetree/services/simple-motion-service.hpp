//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/services/i-motion-service.hpp"

namespace bte {
class SimpleMotionService : public IMotionService
{
public:
    SimpleMotionService(MotionModel& model);

    const MotionModel& model() const override;
    void               move(const units::MotionProfile& mp) override;
    void               stop() override;

private:
    MotionModel* m_model = nullptr;
};
}  // namespace bte