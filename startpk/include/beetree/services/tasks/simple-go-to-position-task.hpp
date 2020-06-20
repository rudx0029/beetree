#pragma once

#include "beetree/controllers/goal-controller.hpp"
#include "beetree/models/navigation-model.hpp"
#include "beetree/services/core/i-runnable.hpp"
#include "beetree/services/i-motion-service.hpp"
#include "beetree/units/coordinate.hpp"

namespace bte {
class SimpleGoToPositionTask : public IRunnable
{
public:
    SimpleGoToPositionTask() = default;

    struct Config
    {
        ///
        /// threshold that informs controller to slow down
        ///
        units::Length near_pos_threshold;
        ///
        /// threshold that informs this task has made it to the position and
        /// is done
        ///
        units::Length at_pos_threshold;
        ///
        /// PID configuration for the goal controller.
        ///
        PID::Config goal_pid_config;
        ///
        /// nominal velocity of the robot ... it's normal velocity
        ///
        units::Velocity travel_velocity;
    };

    void configure(IMotionService& motion_svc, NavigationModel& nav_model, const Config& cfg);

    void initialize(const units::Coordinate& target);
    bool run() override;

private:
    units::Length    m_at_pos_threshold;
    GoalController   m_ctrl;
    NavigationModel* m_nav_model  = nullptr;
    IMotionService*  m_motion_svc = nullptr;
};
}  // namespace bte