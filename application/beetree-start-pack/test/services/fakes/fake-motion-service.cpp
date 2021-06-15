//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "fake-motion-service.hpp"

namespace bte {
namespace test {
namespace internal {
using namespace units::literals;

const MotionModel& FakeMotionService::model() const { return fake_model; }
void FakeMotionService::move(const units::MotionProfile& mp) { fake_model.commanded = mp; }
void FakeMotionService::stop() { fake_model.commanded = {0_mps, 0_mpss, 0_radps}; }

}  // namespace internal
}  // namespace test
}  // namespace bte