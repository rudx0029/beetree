//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/services/simple-bump-service.hpp"
#include "beetree/models/data/simple-reflex-ids.hpp"
#include "beetree/units/units.hpp"

namespace bte {
using namespace units::literals;
using units::Angle;
using units::make;
using units::scl;
using BumpIterator = IBumpService::BumpIterator;

constexpr std::size_t  NUM_ZONES      = 32;
constexpr units::Angle ANGLE_PER_ZONE = 196350_urad;

SimpleBumpService::SimpleBumpService(BumpModel& model) : m_model(&model) {}

Reflex SimpleBumpService::get_reflex() const { return simple_reflex_ids::BUMP_REFLEX; }

bool SimpleBumpService::is_bumping() const { return m_model->bump_zone != 0; }

// this will always be 0 when the robot has 1 sensor mounted at the front
Angle SimpleBumpService::bump_incidence() const
{
    Angle angle = 0_deg;
    // todo: this probably should just be a model parameter and filled

    for (std::size_t i = 0; i < (NUM_ZONES / 2); i++)
    {
        // Look CCW
        if (m_model->bump_zone & (1 << i))
        {
            angle = ANGLE_PER_ZONE * make<scl>(i);
            break;
        }
        // Look CW
        if (m_model->bump_zone & (1 << (NUM_ZONES - 1 - i)))
        {
            angle = ANGLE_PER_ZONE * make<scl>(NUM_ZONES - 1 - i);
            break;
        }
    }
    return units::bound(angle);
}

void SimpleBumpService::record_bump(const units::Pose2D& position, units::Angle incidence)
{
    // save the latest bump
    m_one_bump_history[0] = Bump{position, incidence, Clock::now()};
    m_num_bumps           = 1;
}

BumpIterator SimpleBumpService::begin() const { return &m_one_bump_history[0]; }
BumpIterator SimpleBumpService::end() const { return &m_one_bump_history[m_num_bumps]; }
void         SimpleBumpService::clear_history() { m_num_bumps = 0; }

}  // namespace bte
