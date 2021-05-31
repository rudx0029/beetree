//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE.txt', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

namespace bte {

///
/// Provides reference storage for 1 instance of a given type. It is assumed the application will
/// persist the blackboard sources and the blackboard will provide a reference to the source.
///
/// The blackboard should be accessed by a node's implementation or a tree's API in order to
/// retrieve models and services required by the node or tree but persist in the application.
///
struct blackboard
{
    ///
    /// Installs the source to the blackboard. The source will be considered readonly when
    /// accessed from the blackboard. The readonly source should be installed when the
    /// application is booting up.
    ///
    template <class T>
    static void install_readonly(T& source);

    ///
    /// Installs the source to the blackboard. The source will be considered writeable when
    /// accessed from the blackboard. The source should be installed when the
    /// application is booting up.
    ///
    template <class T>
    static void install_writeable(T& source);

    ///
    /// Gets the readonly source of type T regardless if it is installed writeable
    /// (``blackboard::install_writeable<T>``) or readonly (``blackboard::install_readonly<T>``).
    /// The method returns ``nullptr`` when the source does not exist.
    ///
    template <class T>
    static const T* get();

    ///
    /// Similar to ``blackboard::get<T>`` but ``asserts`` the source exists.
    ///
    template <class T>
    static const T* get_assert();

    ///
    /// Gets the writeable source of type T only if it is installed writeable
    /// (``blackboard::install_writeable<T>``). The method returns ``nullptr`` when the source does
    /// not exist or when the source of type ``T`` is installed readonly
    /// (``blackboard::install_readonly<T>``)
    ///
    template <class T>
    static T* update();

    ///
    /// Similar to ``blackboard::update<T>`` but ``asserts`` the source exists and is writeable.
    ///
    template <class T>
    static T* update_assert();

private:
    template <class T>
    struct source
    {
        static T*   value;
        static bool is_readonly;
    };

    static void assert_valid_source(const void* ptr);
};

template <class T>
void blackboard::install_readonly(T& src)
{
    blackboard::source<T>::value       = &src;
    blackboard::source<T>::is_readonly = true;
}

template <class T>
void blackboard::install_writeable(T& src)
{
    blackboard::source<T>::value       = &src;
    blackboard::source<T>::is_readonly = false;
}

template <class T>
const T* blackboard::get()
{
    return blackboard::source<T>::value;
}

template <class T>
const T* blackboard::get_assert()
{
    auto src = blackboard::source<T>::value;
    assert_valid_source(src);
    return src;
}

template <class T>
T* blackboard::update()
{
    T* src = nullptr;
    if (!blackboard::source<T>::is_readonly)
    {
        src = blackboard::source<T>::value;
    }
    return src;
}

template <class T>
T* blackboard::update_assert()
{
    T* src = blackboard::update<T>();
    assert_valid_source(src);
    return src;
}

template <class T>
T* blackboard::source<T>::value = nullptr;
template <class T>
bool blackboard::source<T>::is_readonly = true;

}  // namespace bte