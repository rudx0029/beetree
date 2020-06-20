#include "beetree/facilities/filters/motor-control-filter-sm.hpp"

namespace bte {
using namespace units;
using namespace units::literals;

MotorPWM MotorControlFilterSM::no_motion(const MotorControlInput& in)
{
    Direction motor_direction;

    if (in.commanded_velocity > m_min_vel_threshold)
    {
        motor_direction = Direction::FORWARD;
        m_active        = motionStates::START_MOTION_FWD;
    }
    else if (in.commanded_velocity < m_min_vel_threshold)
    {
        motor_direction = Direction::REVERSE;
        m_active        = motionStates::START_MOTION_REV;
    }
    m_state_count = 0;

    return {0_scl, motor_direction};
}
MotorPWM MotorControlFilterSM::start_motion_fwd(const MotorControlInput& in)
{
    Direction     motor_direction = Direction::FORWARD;
    units::Scalar pwm             = 512_scl;

    if (m_state_count++ > 10)
    {
        m_active = motionStates::CONTINUE_MOTION_FWD;
    }

    return {pwm, motor_direction};
}
MotorPWM MotorControlFilterSM::continue_motion_fwd(const MotorControlInput& in)
{
    Direction     motor_direction = Direction::FORWARD;
    units::Scalar pwm             = 0_scl;

    /// TODO - CHECK FOR REVERSE CHANGES....
    if (abs(in.commanded_velocity) >= m_min_vel_threshold)
    {
        pwm = m_pid.step(cast<Scalar>(in.commanded_velocity), cast<Scalar>(in.measured_velocity));
        if (pwm < 0_scl)
        {
            pwm = 0_scl;
        }
    }
    else
    {
        // run the pid with command_velocity to 0 but do not update the pwm
        m_pid.step(0_scl, cast<Scalar>(in.measured_velocity));
        m_active = motionStates::ZERO_CROSS_FWD;
    }

    return {pwm, motor_direction};
}
MotorPWM MotorControlFilterSM::zero_cross_fwd(const MotorControlInput& in)
{
    Direction     motor_direction = Direction::FORWARD;
    units::Scalar pwm             = 0_scl;

    //
    /// TODO : NOT HANDLING CASE OF CHANGE OF DIRECTION.
    //

    if (abs(in.commanded_velocity) >= m_min_vel_threshold)
    {
        pwm = m_pid.step(cast<Scalar>(in.commanded_velocity), cast<Scalar>(in.measured_velocity));
        if (pwm < 0_scl)
        {
            pwm = 0_scl;
        }
        m_active = motionStates::CONTINUE_MOTION_FWD;
    }
    else
    {
        // run the pid with command_velocity to 0 but do not update the pwm
        if (in.measured_velocity < 1_mmps)
        {
            m_active = motionStates::NO_MOTION;
        }
        else
        {
            m_pid.step(0_scl, cast<Scalar>(in.measured_velocity));
        }
    }

    return {pwm, motor_direction};
}

MotorPWM MotorControlFilterSM::start_motion_rev(const MotorControlInput& in)
{
    Direction     motor_direction = Direction::REVERSE;
    units::Scalar pwm             = 512_scl;

    if (m_state_count++ > 10)
    {
        m_active = motionStates::CONTINUE_MOTION_REV;
    }

    return {pwm, motor_direction};
}
MotorPWM MotorControlFilterSM::continue_motion_rev(const MotorControlInput& in)
{
    Direction     motor_direction = Direction::REVERSE;
    units::Scalar pwm             = 0_scl;

    /// TODO - CHECK FOR REVERSE CHANGES....
    if (abs(in.commanded_velocity) >= m_min_vel_threshold)
    {
        pwm = m_pid.step(cast<Scalar>(in.commanded_velocity), cast<Scalar>(in.measured_velocity));
        if (pwm < 0_scl)
        {
            pwm = -pwm;
        }
        else
        {
            pwm = 0_scl;
        }
    }
    else
    {
        // run the pid with command_velocity to 0 but do not update the pwm
        m_pid.step(0_scl, cast<Scalar>(in.measured_velocity));
        m_active = motionStates::ZERO_CROSS_FWD;
    }

    return {pwm, motor_direction};
}
MotorPWM MotorControlFilterSM::zero_cross_rev(const MotorControlInput& in)
{
    Direction     motor_direction = Direction::REVERSE;
    units::Scalar pwm             = 0_scl;
    //
    /// TODO : NOT HANDLING CASE OF CHANGE OF DIRECTION.
    //
    if (abs(in.commanded_velocity) >= m_min_vel_threshold)
    {
        pwm = m_pid.step(cast<Scalar>(in.commanded_velocity), cast<Scalar>(in.measured_velocity));
        if (pwm < 0_scl)
        {
            pwm = -pwm;
        }
        else
        {
            pwm = 0_scl;
        }
        m_active = motionStates::CONTINUE_MOTION_REV;
    }
    else
    {
        // run the pid with command_velocity to 0 but do not update the pwm
        if (in.measured_velocity < 1_mmps)
        {
            m_active = motionStates::NO_MOTION;
        }
        else
        {
            m_pid.step(0_scl, cast<Scalar>(in.measured_velocity));
        }
    }
    return {pwm, motor_direction};
}
MotorPWM MotorControlFilterSM::sm(const MotorControlInput& in)
{
    Direction motor_direction = Direction::REVERSE;
    MotorPWM  pwm;

    switch (m_active)
    {
        case motionStates::NO_MOTION:
            pwm = no_motion(in);
            break;
        case motionStates::START_MOTION_FWD:
            pwm = start_motion_fwd(in);
            break;
        case motionStates::CONTINUE_MOTION_FWD:
            pwm = continue_motion_fwd(in);
            break;
        case motionStates::ZERO_CROSS_FWD:
            pwm = zero_cross_fwd(in);
            break;
        case motionStates::START_MOTION_REV:
            pwm = start_motion_rev(in);
            break;
        case motionStates::CONTINUE_MOTION_REV:
            pwm = continue_motion_rev(in);
            break;
        case motionStates::ZERO_CROSS_REV:
            pwm = zero_cross_rev(in);
            break;
    }
    return pwm;
}

void MotorControlFilterSM::configure(units::Velocity min_vel_threshold, const PID::Config& pid)
{
    m_min_vel_threshold = min_vel_threshold;
    m_pid.configure(pid);
    m_active = motionStates::NO_MOTION;
}

MotorPWM MotorControlFilterSM::apply(const MotorControlInput& in)
{
    MotorPWM pwm = sm(in);
    return pwm;
}
}  // namespace bte