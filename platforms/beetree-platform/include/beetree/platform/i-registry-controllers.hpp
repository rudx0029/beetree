//------------------------------------------------------------------------------
// Copyright (C) 2021 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

namespace bte {
class IRegistryRxController
{
public:
    virtual void sync() = 0;
};

class IRegistryTxController {
public:
    virtual void flush() = 0;
};

class IRegistryTickController {
public:
    virtual void tick() = 0;
};
}  // namespace bte