#pragma once

#include "beetree/btos/clock.hpp"
#include "beetree/facilities/pipes/encoder-reading.hpp"
#include "beetree/facilities/pipes/motion.hpp"

namespace bte {
class EncoderFilter
{
public:
    void   configure(Clock::milliseconds dt,
                     units::Length       wheel_dist_per_tick,
                     units::Scalar       reload = 32768_scl);
    Motion apply(const EncoderReading& input);
    void   reset();

private:
    units::Length   measure_distance(const EncoderReading& input) const;
    units::Velocity measure_velocity(units::Length delta_len) const;
    units::Accel    measure_accel(units::Velocity cur, units::Velocity prev) const;

    Clock::milliseconds m_dt;
    units::Length       m_wheel_dist_per_tick;
    units::Scalar       m_reload = 32768_scl;

    units::Scalar   m_last_ticks;
    units::Velocity m_last_vel;
};
}  // namespace bte