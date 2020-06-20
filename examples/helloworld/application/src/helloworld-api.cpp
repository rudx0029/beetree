//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE.txt', which is part of this source code package.
//------------------------------------------------------------------------------

#include "helloworld/helloworld-api.hpp"
#include "beetree/nodes/blackboard.hpp"
#include "helloworld/helloworld-model.hpp"

namespace helloworld {
bool is_user_btn_depressed()
{
    auto model = bte::blackboard::get_assert<HelloworldModel>();
    if (model)
    {
        return model->user_btn_depressed;
    }
    return false;
}
}  // namespace helloworld