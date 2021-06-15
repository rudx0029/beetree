#pragma once

#include "beetree/controllers/pid.hpp"
#include "beetree/models/navigation-model.hpp"
#include "beetree/services/core/i-runnable.hpp"
#include "beetree/services/i-motion-service.hpp"

namespace bte {
class SimpleRotateTask : public IRunnable
{
public:
    SimpleRotateTask() = default;

    struct Config
    {
        ///
        /// angle/heading threshold for determining when the rotate
        /// completes i.e. abs(target-actual) < threshold
        ///
        units::Angle threshold;
        ///
        /// angular velocity threshold vor determing when the rotate
        /// completes, i.e. abs(actual_ang_vel) < ang_vel_threshold
        ///
        units::AngVelocity ang_vel_threshold;
        ///
        /// PID Configuration for the rotation controller
        ///
        PID::Config pid;
    };

    void configure(IMotionService& motion_svc, NavigationModel& nav_model, const Config& cfg);

    void initialize(units::Angle target_heading);

    bool run() override;

private:
    units::Angle       m_threshold;
    units::AngVelocity m_ang_vel_threshold;
    PID                m_pid;
    NavigationModel*   m_nav_model  = nullptr;
    IMotionService*    m_motion_svc = nullptr;
};
}  // namespace bte