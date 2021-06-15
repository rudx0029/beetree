#pragma once

namespace bte {
struct UserEvent
{
    bool play_pause_toggle = false;
    bool stop              = false;
    bool easter_egg        = false;

    UserEvent() = default;
    UserEvent(bool ppt, bool s, bool ee) : play_pause_toggle(ppt), stop(s), easter_egg(ee) {}
};
}  // namespace bte