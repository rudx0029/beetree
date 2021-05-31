//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

namespace bte {
class IFatalListener
{
public:
    IFatalListener()          = default;
    virtual ~IFatalListener() = default;

    virtual void on_fatal_error() = 0;
};
}  // namespace bte