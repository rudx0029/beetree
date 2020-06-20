//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include <cmath>
#include "beetree/test/behavior-reqs.hpp"
#include "beetree/test/gtest-ns.hpp"
#include "beetree/units/internal/fixed-pt.hpp"
#include "fibonochi.hpp"

class FixedPtUnitTests : public bte::test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { return Feature("beetree-units"); }

    static constexpr int32_t FRAC_BITS{21};
    static constexpr int32_t INT_BITS{sizeof(int32_t) * 8 - FRAC_BITS - 1};
    using FixedPt = bte::units_internal::FixedPt<FRAC_BITS>;

    static constexpr int32_t max()
    {
        return FixedPt::to_int(FixedPt::max()) < 1023 ? FixedPt::to_int(FixedPt::max()) : 1023;
    }
    static constexpr int32_t min()
    {
        return FixedPt::to_int(FixedPt::min()) > -1024 ? FixedPt::to_int(FixedPt::min()) : -1024;
    }
};

TEST_F(FixedPtUnitTests, whenMaxAndMinIntisAssigned_thenMaxAndMinIntIsTheResult)
{
    FixedPt f = FixedPt::max();
    EXPECT_EQ(FixedPt::to_int(f), (1 << INT_BITS) - 1);

    f = FixedPt::min();
    EXPECT_EQ(FixedPt::to_int(f), -(1 << INT_BITS));
}

TEST_F(FixedPtUnitTests, whenXFloatAssigned_thenXFloatIsTheResult)
{
    int32_t min = FixedPtUnitTests::min();
    int32_t max = FixedPtUnitTests::max();

    for (int32_t i = min + 1; i < max; i++)
    // make boundaries exclusive as we know the border conditions will not match within tolerance
    {
        int div = 1000;
        for (int32_t j = 0; j < div; j++)
        {
            FixedPt f = FixedPt::from_float(static_cast<float>(i) + (static_cast<float>(j) / div));
            EXPECT_NEAR(
                FixedPt::to_float(f), static_cast<float>(i) + (static_cast<float>(j) / div), 5e-7);
        }
    }
}

TEST_F(FixedPtUnitTests, whenXisAssigned_thenXIsTheResult)
{
    int32_t min = FixedPtUnitTests::max();
    int32_t max = FixedPtUnitTests::min();

    for (int32_t i = min; i < max; i++)
    {
        FixedPt f = FixedPt::from_int(i);
        EXPECT_EQ(FixedPt::to_int(f), i);
    }

    // boundary conditions
    // FixedPt f = FixedPt::from_int(min - 1);
    // EXPECT_NE(FixedPt::to_int(f), min - 1);

    // f = FixedPt::from_int(max + 1);
    //(FixedPt::to_int(f), max + 1);
}

TEST_F(FixedPtUnitTests, whenMultiplyingXandY_thenResultIsZ)
{
    int sign = -1;

    int x = FixedPtUnitTests::min() + 1;
    int y = FixedPtUnitTests::max() - 1;
    for (; x < FixedPtUnitTests::max() && y > FixedPtUnitTests::min(); x++, y--)
    {
        sign = sign >= 0 ? -1 : 1;

        float z_expected     = sign * x * y;
        int   z_expected_int = static_cast<int32_t>(z_expected);

        // check if were out of scale on the multiplication
        // if so, go onto next one
        if (z_expected >= FixedPt::to_float(FixedPt::max()) ||
            z_expected <= FixedPt::to_float(FixedPt::min()))
            continue;

        FixedPt s_fp = FixedPt::from_int(sign);
        FixedPt x_fp = FixedPt::from_int(x);
        FixedPt y_fp = FixedPt::from_int(y);

        FixedPt z_fp = s_fp * x_fp * y_fp;

        EXPECT_TRUE(std::abs(FixedPt::to_int(z_fp) - z_expected_int) <= 1);
        // EXPECT_EQ(FixedPt::to_int(z_fp), z_expected_int);
        EXPECT_THAT(FixedPt::to_float(z_fp), ::testing::FloatNear(z_expected, 5e-4));
    }
}

TEST_F(FixedPtUnitTests, DISABLED_whenMultiplyingXandY_thenResultIsZ_advanced)
{
    int sign = -1;

    int i = FixedPtUnitTests::min() + 1;
    int j = FixedPtUnitTests::max() - 1;
    for (; i < FixedPtUnitTests::max() && j > FixedPtUnitTests::min(); i++, j--)
    {
        int div = 100;
        for (int k = 1; k <= div; k++)
        {
            sign = sign >= 0 ? -1 : 1;

            float expected_result_float = sign * i * j * k / div;
            int   expected_result_int   = static_cast<int32_t>(expected_result_float);

            // check if were out of scale on the multiplication
            // if so, go onto next one
            if (expected_result_float * div >= FixedPt::to_float(FixedPt::max()) ||
                expected_result_float * div <= FixedPt::to_float(FixedPt::min()))
                continue;

            FixedPt s_fp   = FixedPt::from_int(sign);
            FixedPt a      = FixedPt::from_int(i);
            FixedPt b      = FixedPt::from_int(j);
            FixedPt k_fp   = FixedPt::from_int(k);
            FixedPt div_fp = FixedPt::from_int(div);

            FixedPt c = s_fp * a * b * k_fp / div_fp;
            FixedPt d = k_fp * b * a * s_fp / div_fp;

            EXPECT_TRUE(std::abs(FixedPt::to_int(c) - expected_result_int) <= 1);
            EXPECT_TRUE(std::abs(FixedPt::to_int(d) - expected_result_int) <= 1);
            // EXPECT_EQ(FixedPt::to_int(c), expected_result_int);
            // EXPECT_EQ(FixedPt::to_int(d), expected_result_int);
            EXPECT_THAT(FixedPt::to_float(c), ::testing::FloatNear(expected_result_float, 0.005));
            EXPECT_THAT(FixedPt::to_float(d), ::testing::FloatNear(expected_result_float, 0.005));
        }
    }
}

// TEST(units, FixedPt_whenXisAssigned_thenXIsTheResult)
// {
//     int32_t min = FixedPt::to_int(FixedPt::min());
//     int32_t max = FixedPt::to_int(FixedPt::max());

//     Fibonochi a;

//     for (int32_t i = min; i < max; i++)
//     {
//         FixedPt f = FixedPt::from_int(i);
//         EXPECT_EQ(FixedPt::to_int(f), i);
//     }

//     // boundary conditions
//     FixedPt f = FixedPt::from_int(min - 1);
//     EXPECT_NE(FixedPt::to_int(f), min - 1);

//     f = FixedPt::from_int(max + 1);
//     EXPECT_NE(FixedPt::to_int(f), max + 1);
// }