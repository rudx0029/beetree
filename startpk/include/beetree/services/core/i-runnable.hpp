//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

namespace bte {
class IRunnable
{
public:
    // construct - destruct
    IRunnable()          = default;
    virtual ~IRunnable() = default;

    // interface
    virtual bool run() = 0;
};
}  // namespace bte