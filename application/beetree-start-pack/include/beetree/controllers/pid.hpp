#pragma once

#include "beetree/btos/clock.hpp"
#include "beetree/units/units.hpp"

namespace bte {
class PID
{
public:
    struct Config
    {
        units::Scalar       kp;  ///< Proportional 'P' gain
        units::Scalar       ki;  ///< Integral 'I' gain
        units::Scalar       kd;  ///< Derivative 'D' gain
        Clock::milliseconds ts;  ///< sampling period
        units::Scalar       max_cmd;
        units::Scalar       min_cmd;  //-512_scl;
        units::Scalar       bias;     ///< bias gain
    };

    void reset();
    void configure(const Config& config);

    units::Scalar step(units::Scalar set_point, units::Scalar feed_back);
    units::Scalar step(units::Angle set_point,
                       units::Angle feed_back);  // special case for angles as they must be bounded

    // int32_t step(int32_t)
private:
    units::Scalar internal_step(units::Scalar err, units::Scalar derr);

    void anti_windup_adjustment(const units::Scalar& output,
                                      const units::Scalar& P,
                                      const units::Scalar& D,
                                      const units::Scalar& ts);

    Config        m_config;
    units::Scalar m_sum_err;
    units::Scalar m_last_feed_back;
};
}  // namespace bte