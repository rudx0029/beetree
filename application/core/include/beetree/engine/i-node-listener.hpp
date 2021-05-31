//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/node.hpp"

namespace bte {
class INodeListener
{
public:
    INodeListener()          = default;
    virtual ~INodeListener() = default;

    virtual void on_node_active(const Node& node) = 0;
};
}  // namespace bte