#pragma once

#include "beetree/btos/clock.hpp"
#include "beetree/services/core/i-runnable.hpp"
#include "beetree/units/units.hpp"

namespace bte {
///
/// The Task class provides a common interface for running long
/// tasks in a node provided by a service. A task executes a runnable
/// and provides management, namely timeout management.
///
class Task
{
public:
    using Time = units::Time;

    Task() = default;
    ///
    /// Construct a new Task object.
    ///
    /// ! It is assumed that runnable has been initialized prior to this
    /// @param runnable the task to be run
    /// @param timeout the max length the task can run, must be greater than 0.
    ///
    Task(IRunnable& runnable, Clock::ms timeout)
        : m_runnable(&runnable), m_timeout(timeout), m_start(Clock::now())
    {}
    ///
    /// Executes the runnable while checking for timeout
    ///
    /// @return true while the task is executing
    /// @return false if the task is done running or it timed out, in
    /// which is_timeout will return true
    ///
    bool run() { return is_okay() && m_runnable->run(); }
    ///
    /// @return true the task timedout while running
    /// @return false otherwise
    ///
    bool is_timeout() const { return (m_timeout != 0_s) && Clock::elapsed(m_start) > m_timeout; }

    ///
    /// @return true when the task is valid there is not a timeout
    /// @return false otherwise
    ///
    bool is_okay() const { return m_runnable && !is_timeout(); }

private:
    IRunnable*        m_runnable = nullptr;
    Clock::ms         m_timeout  = 0_s;
    Clock::time_point m_start{{0_s}};
};
}  // namespace bte