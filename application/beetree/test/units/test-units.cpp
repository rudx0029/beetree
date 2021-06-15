#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/test-api/matchers/unit.hpp"
#include "beetree/units/units.hpp"
#include "fibonochi.hpp"

using namespace bte::units::literals;

using bte::test::Fibonochi;
using bte::test::UnitNear;
using bte::units::Angle;
using bte::units::as;
using bte::units::bound;
using bte::units::cast;
using bte::units::deg;
using bte::units::make;
using bte::units::mscl;
using bte::units::PI;
using bte::units::rad;
using bte::units::Scalar;
using bte::units::scl;

class UnitsTests : public bte::test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("beetree-units"); }
};

TEST_F(UnitsTests, whenMultiplyingScalars_thenTheResultIsAScalar)
{
    std::vector<int> fibf = Fibonochi().produce(20);
    std::vector<int> fibb = Fibonochi().produce(20);

    auto iterf = fibf.begin();
    auto iterb = --fibb.end();
    int  sign  = -1;

    for (; iterf != fibf.end(); iterb--, iterf++)
    {
        sign     = sign >= 0 ? -1 : 1;
        Scalar a = make<mscl>(sign * (*iterf));
        Scalar b = make<scl>(*iterb);

        int expected_result_scl  = (sign * (*iterf)) * (*iterb) / 1000.0f;
        int expected_result_mscl = (((sign * (*iterf)) / 1000.0f) * (*iterb)) * 1000.0f;

        Scalar c = a * b;
        Scalar d = b * a;

        EXPECT_EQ(as<scl>(c), expected_result_scl);
        EXPECT_EQ(as<mscl>(c), expected_result_mscl);
        EXPECT_EQ(as<scl>(d), expected_result_scl);
        EXPECT_EQ(as<mscl>(d), expected_result_mscl);
    }
}

TEST_F(UnitsTests, whenDividingScalars_thenTheResultIsAScalar)
{
    std::vector<int> fibf = Fibonochi().produce(20);
    std::vector<int> fibb = Fibonochi().produce(20);

    auto iterf = fibf.begin();
    auto iterb = --fibb.end();
    int  sign  = -1;

    for (; iterf != fibf.end(); iterb--, iterf++)
    {
        int fib_a = *iterf;
        int fib_b = *iterb;

        sign     = sign >= 0 ? -1 : 1;
        Scalar a = make<mscl>(sign * fib_a);
        Scalar b = make<scl>(fib_b);

        int expected_result_scl  = ((sign * fib_a) / 1000.0f) / fib_b;
        int expected_result_mscl = ((sign * fib_a) / 1000.0f) / fib_b * 1000.0f;

        Scalar c = a / b;

        EXPECT_EQ(as<scl>(c), expected_result_scl);
        EXPECT_EQ(as<mscl>(c), expected_result_mscl);
    }
}

TEST_F(UnitsTests, whenCalculatingAngles_thenTheResultOfDegreesAndRadiansIsSame)
{
    // constexpr units::Real tolerance = 0.0001f;
    EXPECT_THAT(360_deg, UnitNear(2_rad * PI, 1_mrad));
    EXPECT_THAT(-315_deg, UnitNear(-1750_mrad * PI, 1_mrad));
    EXPECT_THAT(270_deg, UnitNear(1500_mrad * PI, 1_mrad));
    EXPECT_THAT(-225_deg, UnitNear(-1250_mrad * PI, 1_mrad));
    EXPECT_THAT(180_deg, UnitNear(cast<Angle>(PI), 1_mrad));
    EXPECT_THAT(-135_deg, UnitNear(-750_mrad * PI, 1_mrad));
    EXPECT_THAT(90_deg, UnitNear(PI / 2_rad, 1_mrad));
    EXPECT_THAT(-45_deg, UnitNear(-PI / 4_rad, 1_mrad));
    EXPECT_THAT(0_deg, UnitNear(0_rad * PI, 1_mrad));
}

TEST_F(UnitsTests, whenCalculatingAnglesGreaterThanAbsPI_thenTheResultIsBoundedInPi)
{
    EXPECT_THAT(bound(360_deg), UnitNear(bound(0_rad), 1_mrad));
    EXPECT_THAT(bound(-315_deg), UnitNear(bound(PI / 4_rad), 1_mrad));
    EXPECT_THAT(bound(270_deg), UnitNear(bound(-PI / 2_rad), 1_mrad));
    EXPECT_THAT(bound(-225_deg), UnitNear(bound(750_mrad * PI), 1_mrad));
    EXPECT_THAT(bound(180_deg), UnitNear(bound(cast<Angle>(PI)), 1_mrad));
}