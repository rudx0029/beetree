#include <cmath>
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/units/internal/real.hpp"

using bte::gtest::FloatNear;
using bte::units_internal::Real;
using bte::units_internal::RealMath;

class UnitMathRandTests : public bte::test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("beetree-units"); }
};

TEST_F(UnitMathRandTests, Math_rand_test)
{
    int i;
    for (i = 0; i < 100; i++)
    {
        Real real_rand = RealMath::rand();
        EXPECT_TRUE(
            ((real_rand >= Real::from_float(0.0f)) && (real_rand <= Real::from_float(1.0f))));
    }
}
