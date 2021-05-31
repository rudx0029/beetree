//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/test-api/matchers/unit.hpp"
#include "beetree/units/methods.hpp"

using namespace bte;
using namespace bte::units::literals;

using units::Angle;
using units::Coordinate;
using units::cos;
using units::Length;
using units::Pose2D;
using units::sin;
using units::to_abs_coord;

using test::BehaviorReqTest;
using test::UnitNear;

class UnitMethodTests : public BehaviorReqTest
{
protected:
    const float tolerance = 0.001f;
    static void SetUpTestCase() { Feature("beetree-units"); }

    Coordinate make_coord(Length mag, Angle theta) { return {mag * cos(theta), mag * sin(theta)}; }
};

TEST_F(UnitMethodTests, pivotCoordAroundFrameAt0Theta)
{
    Angle cur_angle;
    Angle interval = 1_rad * units::PI / 6_scl;

    for (int i = 0; i < 12; i++)
    {
        Coordinate c_rel = make_coord(5_m, cur_angle);

        Pose2D p_frame{234_mm, -1148_m, 0_deg};

        Coordinate result = to_abs_coord(c_rel, p_frame);

        EXPECT_THAT(result.x, UnitNear(c_rel.x + p_frame.x, 1_mm));
        EXPECT_THAT(result.y, UnitNear(c_rel.y + p_frame.y, 1_mm));

        cur_angle += interval;
    }
}

TEST_F(UnitMethodTests, pivotCoordAt0ToFrame90)
{
    Coordinate c_rel = make_coord(5_m, 0_deg);

    Pose2D p_frame{234_mm, -1148_m, 90_deg};

    Coordinate result = to_abs_coord(c_rel, p_frame);

    EXPECT_THAT(result.x, UnitNear(c_rel.y + p_frame.x, 1_mm));
    EXPECT_THAT(result.y, UnitNear(c_rel.x + p_frame.y, 1_mm));
}

TEST_F(UnitMethodTests, pivotCoordAt0ToFrameNeg90)
{
    Coordinate c_rel = make_coord(5_m, 0_deg);

    Pose2D p_frame{234_mm, -1148_m, -90_deg};

    Coordinate result = to_abs_coord(c_rel, p_frame);

    EXPECT_THAT(result.x, UnitNear(c_rel.y + p_frame.x, 1_mm));
    EXPECT_THAT(result.y, UnitNear(-c_rel.x + p_frame.y, 1_mm));
}

TEST_F(UnitMethodTests, pivotCoordAt90ToFrame90)
{
    Coordinate c_rel = make_coord(5_m, 90_deg);

    Pose2D p_frame{0_mm, 0_m, 90_deg};

    Coordinate result = to_abs_coord(c_rel, p_frame);

    EXPECT_THAT(result.x, UnitNear(-c_rel.y + p_frame.x, 1_mm));
    EXPECT_THAT(result.y, UnitNear(c_rel.x + p_frame.y, 1_mm));
}

TEST_F(UnitMethodTests, pivotCoordAt90ToFrame90Neg)
{
    Coordinate c_rel = make_coord(5_m, 90_deg);

    Pose2D p_frame{0_mm, 0_m, -90_deg};

    Coordinate result = to_abs_coord(c_rel, p_frame);

    EXPECT_THAT(result.x, UnitNear(c_rel.y + p_frame.x, 1_mm));
    EXPECT_THAT(result.y, UnitNear(c_rel.x + p_frame.y, 1_mm));
}

TEST_F(UnitMethodTests, pivotCoordAt180ToFrame90)
{
    Coordinate c_rel = make_coord(5_m, 180_deg);

    Pose2D p_frame{0_mm, 0_m, 90_deg};

    Coordinate result = to_abs_coord(c_rel, p_frame);

    EXPECT_THAT(result.x, UnitNear(c_rel.y + p_frame.x, 1_mm));
    EXPECT_THAT(result.y, UnitNear(c_rel.x + p_frame.y, 1_mm));
}

TEST_F(UnitMethodTests, pivotCoordAt180ToFrame90Neg)
{
    Coordinate c_rel = make_coord(5_m, 180_deg);

    Pose2D p_frame{0_mm, 0_m, -90_deg};

    Coordinate result = to_abs_coord(c_rel, p_frame);

    EXPECT_THAT(result.x, UnitNear(c_rel.y + p_frame.x, 1_mm));
    EXPECT_THAT(result.y, UnitNear(-c_rel.x + p_frame.y, 1_mm));
}