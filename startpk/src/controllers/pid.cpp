//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/controllers/pid.hpp"

namespace bte {
using namespace units::literals;
using units::Angle;
using units::bound;
using units::cast;
using units::Scalar;

void PID::configure(const PID::Config& config) { m_config = config; }

void PID::reset()
{
    m_sum_err        = 0_scl;
    m_last_feed_back = 0_scl;
}

void PID::anti_windup_adjustment(const Scalar& output,
                                       const Scalar& P,
                                       const Scalar& D,
                                       const Scalar& ts)
{
    if (ts != 0_scl && m_config.ki != 0_scl)
    {
        m_sum_err = (output - P - D - m_config.bias) / (m_config.ki * ts);
    }
}

Scalar PID::step(Angle set_point, Angle feed_back)
{
    Angle err = bound(set_point - feed_back);
    Angle derr =
        bound(1_rad * m_last_feed_back - feed_back);  // use last - cur since the error signal is
                                                      // not used. This keeps the d gain positive
    m_last_feed_back = cast<Scalar>(feed_back);

    return internal_step(cast<Scalar>(err), cast<Scalar>(derr));
}

Scalar PID::step(Scalar set_point, Scalar feed_back)
{
    Scalar error = set_point - feed_back;
    Scalar delta_err =
        m_last_feed_back - feed_back;  // use last - cur since the error signal is not used
    m_last_feed_back = feed_back;

    return internal_step(error, delta_err);
}

Scalar PID::internal_step(Scalar error, Scalar delta_err)
{
    Scalar P  = 0_scl; /*proportional term*/
    Scalar I  = 0_scl; /*integral term*/
    Scalar D  = 0_scl; /*derivative term*/
    Scalar ts = units::make<units::mscl>(m_config.ts.count());

    /* Integrate the error */
    m_sum_err += error;

    /* calculate proportional */
    P = m_config.kp * error;

    /* calculate integral */
    I = m_config.ki * ts * m_sum_err;

    /* calculate derivative */
    if (ts > 0_scl)
    {
        D = m_config.kd * delta_err / ts;
    }

    /* add desired bias value and calculate the manipulated value*/
    Scalar cmd = P + I + D + m_config.bias;

    /* clamp to max and min and back-calculate error
    for antiwindup */
    if (cmd > m_config.max_cmd)
    {
        cmd = m_config.max_cmd;
        anti_windup_adjustment(m_config.max_cmd, P, D, ts);
    }
    else if (cmd < m_config.min_cmd)
    {
        cmd = m_config.min_cmd;
        anti_windup_adjustment(m_config.min_cmd, P, D, ts);
    }

    return cmd;
}
}  // namespace bte