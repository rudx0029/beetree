#pragma once

#include "beetree/btos/clock.hpp"
#include "beetree/facilities/pipes/user-action.hpp"
#include "beetree/facilities/pipes/user-event.hpp"
#include "beetree/units/units.hpp"

namespace bte {
/**
 * @brief Detects and manages simple button events
 *
 * | Button Clicks | Event             |
 * | :-----------: | :---------------- |
 * | 1             | Play,Pause Toggle |
 * | 2             | Stop              |
 * | 3             | Easter Egg        |
 *
 */

class UserEventFilter
{
public:
    UserEvent apply(const UserAction& input);

private:
    void on_play_pause() {}
    void on_stop() {}
    void on_easter_egg() {}

    bool              m_last_is_pressed = false;
    int32_t           m_btn_cnt         = 0;
    Clock::time_point m_last_btn_press{0_ms};
};
}  // namespace bte