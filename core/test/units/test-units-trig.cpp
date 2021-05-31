//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include <cmath>
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/units/internal/real.hpp"

using bte::gtest::FloatNear;
using bte::units_internal::Real;
using bte::units_internal::RealMath;

class UnitMathTrigTests : public bte::test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("beetree-units"); }
};

TEST_F(UnitMathTrigTests, sin_whenInvoked_thenItMatchesStdLib)
{
    float range_min = -3 * M_PI;
    float range_max = 3 * M_PI;
    float step_size = 0.1;
    float tolerance = 0.001;
    float err_sum   = 0;
    int   count     = 0;

    float cur = range_min;
    while (cur <= range_max)
    {
        Real  real_cur = Real::from_float(cur);
        Real  real_sin = RealMath::sin(real_cur);
        float actual   = Real::to_float(real_sin);
        float expected = std::sin(cur);
        EXPECT_THAT(actual, FloatNear(expected, tolerance));

        err_sum += std::abs(expected - actual);
        count++;
        cur += step_size;
    }

    // printf("sin: average err is %f\n", err_sum / count);
}

TEST_F(UnitMathTrigTests, cos_whenInvoked_thenItMatchesStdLib)
{
    float range_min = -3 * M_PI;
    float range_max = 3 * M_PI;
    float step_size = 0.1;
    float tolerance = 0.001;
    float err_sum   = 0;
    int   count     = 0;

    float cur = range_min;
    while (cur <= range_max)
    {
        Real  real_cur = Real::from_float(cur);
        Real  real_cos = RealMath::cos(real_cur);
        float actual   = Real::to_float(real_cos);
        float expected = std::cos(cur);
        EXPECT_THAT(actual, FloatNear(expected, tolerance));

        err_sum += std::abs(expected - actual);
        count++;
        cur += step_size;
    }

    // std::cout << "cos: average err is " << err_sum / count << std::endl;
}

TEST_F(UnitMathTrigTests, sqrt_whenInvoked_thenItMatchesStdLib)
{
    float range_min = 0;
    float range_max = 100;
    float step_size = 0.1;
    float tolerance = 0.00001;
    float err_sum   = 0;
    int   count     = 0;

    float cur = range_min;
    while (cur <= range_max)
    {
        Real  real_cur  = Real::from_float(cur);
        Real  real_sqrt = RealMath::sqrt(real_cur);
        float actual    = Real::to_float(real_sqrt);
        float expected  = std::sqrt(cur);
        EXPECT_THAT(actual, FloatNear(expected, tolerance));

        err_sum += std::abs(expected - actual);
        count++;
        cur += step_size;
    }

    // std::cout << "sqrt: average err is " << err_sum / count << std::endl;
}

TEST_F(UnitMathTrigTests, atan2_whenInvoked_thenItMatchesStdLib)
{
    float range_min = -2;
    float range_max = 2;
    float step_size = 0.1;
    float tolerance = 0.01;
    float err_sum   = 0;
    int   count     = 0;

    float cur_x = range_min;
    float cur_y = range_max;
    while (cur_x <= range_max)
    {
        Real  real_cur_x = Real::from_float(cur_x);
        Real  real_cur_y = Real::from_float(cur_y);
        Real  real_atan2 = RealMath::atan2(real_cur_y, real_cur_x);
        float actual     = Real::to_float(real_atan2);
        float expected   = std::atan2(cur_y, cur_x);
        EXPECT_THAT(actual, FloatNear(expected, tolerance));

        err_sum += std::abs(expected - actual);
        count++;
        cur_x += step_size;
        cur_y -= step_size;
    }

    // std::cout << "atan2: average err is " << err_sum / count << std::endl;
}