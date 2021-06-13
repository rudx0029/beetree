//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include "beetree/btos/assert.hpp"

namespace bte {

namespace internal {
template <class T>
class ServiceInstall
{
public:
    static T*   get() { return s_service; }
    static void set(T& svc) { s_service = &svc; }

private:
    static T* s_service;
};

template <class T>
T* ServiceInstall<T>::s_service = nullptr;

void assert_valid_svc(const void* ptr);
}  // namespace internal

struct services
{
    template <class T>
    static void install(T& service)
    {
        internal::ServiceInstall<T>::set(service);
    }

    template <class T>
    static bool is_valid()
    {
        return internal::ServiceInstall<T>::get() != nullptr;
    }

    template <class T>
    static T* locate()
    {
        return internal::ServiceInstall<T>::get();
    }

    template <class T>
    static T& pinpoint()
    {
        T* svc = internal::ServiceInstall<T>::get();
        internal::assert_valid_svc(svc);
        return *svc;
    }
};
}  // namespace bte