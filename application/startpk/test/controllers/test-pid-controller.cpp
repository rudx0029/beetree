#include <gtest/gtest.h>
#include "beetree/controllers/pid.hpp"

using namespace bte::units;
using namespace bte::units::literals;
using bte::PID;

TEST(controllers, PID_whenStepWithPGain_thenCommandIsOppositeOfFeedback)
{
    PID::Config cfg;
    cfg.kp      = 1_scl;
    cfg.max_cmd = 100_scl;
    cfg.min_cmd = -100_scl;

    PID pid;
    pid.configure(cfg);

    Scalar step      = 500_mscl;
    Scalar feed_back = cfg.min_cmd;

    while (feed_back < cfg.max_cmd)
    {
        Scalar cmd = pid.step(0_scl, feed_back);
        EXPECT_TRUE(cmd == -feed_back);

        feed_back += step;
    }
}

TEST(controllers, PID_whenStepWithIGain_thenCommandIsTheOpposingSumOfTheFeedback)
{
    PID::Config cfg;
    cfg.ki      = 1_scl;
    cfg.ts      = 1_s;
    cfg.max_cmd = 1000_scl;
    cfg.min_cmd = -1000_scl;

    PID pid;
    pid.configure(cfg);

    Scalar step         = 500_mscl;
    Scalar feed_back    = -5_scl;
    Scalar expected_cmd = -feed_back;
    Scalar cmd          = 1_scl;  // init not to zero for final check

    while (feed_back <= 5_scl)
    {
        cmd = pid.step(0_scl, feed_back);
        EXPECT_TRUE(cmd == expected_cmd);

        feed_back += step;
        expected_cmd += -feed_back;
    }

    EXPECT_TRUE(cmd == 0_scl);
}

TEST(controllers, PID_whenStepWithDGain_thenCommandIsOppositeOfStepDirection)
{
    PID::Config cfg;
    cfg.kd      = 1_scl;
    cfg.ts      = 1_s;
    cfg.max_cmd = 1000_scl;
    cfg.min_cmd = -1000_scl;

    PID pid;
    pid.configure(cfg);

    Scalar step      = 500_mscl;
    Scalar feed_back = -5_scl;
    Scalar cmd       = 1_scl;  // init not to zero for final check

    pid.step(0_scl,
             feed_back - step);  // warm up the pid controller so there isn't a huge step response.

    while (feed_back <= 5_scl)
    {
        cmd = pid.step(0_scl, feed_back);
        // ignore first resu
        EXPECT_TRUE(cmd == -step);

        feed_back += step;
    }
}

TEST(controllers, PID_whenStepWithDGainOnConstantError_thenCommandIsZero)
{
    PID::Config cfg;
    cfg.kd      = 1_scl;
    cfg.ts      = 1_s;
    cfg.max_cmd = 1000_scl;
    cfg.min_cmd = -1000_scl;

    PID pid;
    pid.configure(cfg);

    Scalar step      = 500_mscl;
    Scalar feed_back = -5_scl;
    Scalar cmd       = 1_scl;  // init not to zero for final check

    for (int i = 0; i < 100; i++)
    {
        pid.step(0_scl,
                 feed_back);  // warm up the pid controller so there isn't a huge step response.
    }

    EXPECT_TRUE(0_scl == (pid.step(0_scl, feed_back)));
}

TEST(controllers, PID_whenErrorExceedsLimits_thenCommandIsSaturated)
{
    PID::Config cfg;
    cfg.kp      = 1_scl;
    cfg.ts      = 1_s;
    cfg.max_cmd = 1_scl;
    cfg.min_cmd = -1_scl;

    PID pid;
    pid.configure(cfg);

    Scalar step      = 500_mscl;
    Scalar feed_back = -2_scl;
    Scalar cmd       = 1_scl;  // init not to zero for final check

    while (feed_back <= 2_scl)
    {
        cmd = pid.step(0_scl, feed_back);

        if (feed_back < -cfg.max_cmd)
        {
            EXPECT_TRUE(cmd == cfg.max_cmd);
        }
        else if (feed_back > -cfg.min_cmd)
        {
            EXPECT_TRUE(cmd == cfg.min_cmd);
        }
        else
        {
            EXPECT_TRUE(cmd == -feed_back);
        }

        feed_back += step;
    }
}

// todo: test for anti windup
