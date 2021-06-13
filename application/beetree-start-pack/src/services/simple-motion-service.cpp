//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/services/simple-motion-service.hpp"

namespace bte {
using namespace units::literals;

SimpleMotionService::SimpleMotionService(MotionModel& model) : m_model(&model) {}

const MotionModel& SimpleMotionService::model() const { return *m_model; }

void SimpleMotionService::move(const units::MotionProfile& mp) { m_model->commanded = mp; }

void SimpleMotionService::stop() { m_model->commanded = {0_mps, 0_mpss, 0_radps}; }

}  // namespace bte