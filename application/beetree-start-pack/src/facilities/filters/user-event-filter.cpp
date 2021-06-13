//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/facilities/filters/user-event-filter.hpp"

namespace bte {
UserEvent UserEventFilter::apply(const UserAction& input)
{
    UserEvent events{false, false, false};

    if (input.is_btn_pressed != m_last_is_pressed)
    {
        if (!input.is_btn_pressed)
        {
            // button click event
            m_btn_cnt++;
            m_last_btn_press = Clock::now();
        }

        m_last_is_pressed = input.is_btn_pressed;
    }

    if (m_btn_cnt > 0 && Clock::elapsed(m_last_btn_press) >= 500_ms)
    {
        switch (m_btn_cnt)
        {
            case 1:
                events.play_pause_toggle = true;
                break;
            case 2:
                events.stop = true;
                break;
            case 3:
            default:
                events.easter_egg = true;
                break;
        }

        m_btn_cnt = 0;
    }

    return events;
}
}  // namespace bte