//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/services/i-motion-service.hpp"
#include "beetree/test/gtest-ns.hpp"

namespace bte {
namespace test {

///
/// Motion Service Mock Object
/// Prefer FakeMotionService over MockMotionService
///
class MockMotionService : public IMotionService
{
public:
    // provide write access to the model in the unit test
    MotionModel fake_model;

    MOCK_CONST_METHOD0(model, const MotionModel&());
    MOCK_METHOD1(move, void(const units::MotionProfile& mp));
    MOCK_METHOD0(stop, void());

    MockMotionService() { ON_CALL(*this, model()).WillByDefault(gtest::ReturnRef(fake_model)); }
};
}  // namespace test
}  // namespace bte