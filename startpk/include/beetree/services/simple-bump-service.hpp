//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/btos/optional.hpp"
#include "beetree/models/bump-model.hpp"
#include "beetree/services/i-bumper-service.hpp"

namespace bte {
class SimpleBumpService : public IBumpService
{
public:
    SimpleBumpService(BumpModel& model);

    Reflex get_reflex() const override;

    bool         is_bumping() const override;
    units::Angle bump_incidence() const override;

    void record_bump(const units::Pose2D& position, units::Angle incidence) override;

    BumpIterator begin() const override;
    BumpIterator end() const override;
    void         clear_history() override;

private:
    BumpModel*  m_model = nullptr;
    Bump        m_one_bump_history[1];
    std::size_t m_num_bumps = 0;
};
}  // namespace bte