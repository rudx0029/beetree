#include "beetree/services/tasks/simple-rotate-task.hpp"
#include "beetree/units/methods.hpp"
#include "beetree/units/motion-profile.hpp"

namespace bte {
using namespace units::literals;
using units::abs;
using units::Angle;
using units::AngVelocity;
using units::bound;
using units::MotionProfile;
using units::radps;

void SimpleRotateTask::configure(IMotionService&  motion_svc,
                                 NavigationModel& nav_model,
                                 const Config&    cfg)
{
    m_motion_svc        = &motion_svc;
    m_nav_model         = &nav_model;
    m_threshold         = cfg.threshold;
    m_ang_vel_threshold = cfg.ang_vel_threshold;
    m_pid.configure(cfg.pid);
}

void SimpleRotateTask::initialize(units::Angle target_heading)
{
    // since we are rotating in place update the commanded pose with the
    // current pose
    m_nav_model->commanded_pose         = m_nav_model->measured_pose;
    m_nav_model->commanded_pose.heading = target_heading;

    m_pid.reset();
}

bool SimpleRotateTask::run()
{
    const auto& commanded_pose = m_nav_model->commanded_pose;
    const auto& measured_pose  = m_nav_model->measured_pose;

    Angle delta_theta = bound(commanded_pose.heading - measured_pose.heading);

    // use the current heading and angulare velocity to see if the task is
    // complete
    bool is_done = (abs(delta_theta) <= m_threshold) &&
                   (abs(m_motion_svc->model().measured.angularVelocity) <= m_ang_vel_threshold);

    if (!is_done)
    {
        AngVelocity result = 1_rps * m_pid.step(commanded_pose.heading, measured_pose.heading);
        m_motion_svc->move({0_mps, 0_mpss, result});
    }

    return !is_done;
}
}  // namespace bte