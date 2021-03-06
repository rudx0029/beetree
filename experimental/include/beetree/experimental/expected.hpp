//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
// The contents of this file are adapted from the TartanLlama `expected` library
// https://github.com/TartanLlama/expected
// 
//------------------------------------------------------------------------------
#pragma once

#include <cassert>
#include <functional>
#include <type_traits>
#include <variant>
#include "beetree/btos/assert.hpp"
#include "beetree/experimental/stdcpp20.hpp"
#include "beetree/experimental/tokens.hpp"

namespace bte_experimental {

template <class T>
struct unexpected
{
    using type = T;

    unexpected() = delete;
    explicit unexpected(const T& v) noexcept : m_value(v) {}
    explicit unexpected(T&& v) noexcept : m_value(std::move(v)) {}

    template <class... Args>
    explicit unexpected(std::in_place_t, Args&&... args) : m_value(std::forward<Args>(args)...)
    {}

    const T& value() const& noexcept { return m_value; }
    T&&      value() && noexcept { return std::move(m_value); }

    const T& operator*() const& noexcept { return value(); }
    T&&      operator*() && noexcept { return std::move(*this).value(); }

    const T* operator->() const noexcept { return std::addressof(value()); }

private:
    T m_value;
};

template <class T>
unexpected<std::remove_cv_t<T>> make_unexpected(T&& value)
{
    return {std::forward<T>(value)};
}

template <class T, class... Args>
unexpected<std::remove_cv_t<T>> make_unexpected(std::in_place_t, Args&&... args)
{
    return {T{std::forward<Args>(args)...}};
}

template <class T, class E>
class expected
{
public:
    using value_type      = T;
    using error_type      = E;
    using unexpected_type = unexpected<error_type>;

    expected() = delete;
    expected(const value_type& v) noexcept : m_storage(v) {}
    expected(const unexpected_type& e) noexcept : m_storage(e) {}
    expected(value_type&& v) noexcept : m_storage(std::move(v)) {}
    expected(unexpected_type&& e) noexcept : m_storage(std::move(e)) {}

    template <class... Args>
    explicit expected(std::in_place_t, Args&&... args)
        : m_storage(value_type{std::forward<Args>(args)...})
    {}

    expected<T, E>& operator=(const value_type& other) noexcept
    {
        m_storage = other;
        return *this;
    }

    expected<T, E>& operator=(value_type&& other) noexcept
    {
        m_storage = std::move(other);
        return *this;
    }

    expected<T, E>& operator=(const unexpected_type& other) noexcept
    {
        m_storage = other;
        return *this;
    }

    expected<T, E>& operator=(unexpected_type&& other) noexcept
    {
        m_storage = std::move(other);
        return *this;
    }

    bool is_okay() const noexcept
    {
        auto has_value = std::get_if<value_type>(&m_storage) != nullptr;
        auto has_error = std::get_if<unexpected_type>(&m_storage) != nullptr;

        bte::assert_true(has_value ^ has_error, tokens::FatalExpectedInBadState);
        return has_value;
    }
    operator bool() const noexcept { return is_okay(); }

    const value_type& value() const& noexcept
    {
        bte::assert_true(is_okay(), tokens::FatalExpectedValueEmpty);
        return std::get<value_type>(m_storage);
    }

    value_type&& value() && noexcept
    {
        bte::assert_true(is_okay(), tokens::FatalExpectedValueEmpty);
        return std::get<value_type>(std::move(m_storage));
    }

    const value_type& operator*() const& noexcept { return value(); }
    value_type&&      operator*() && noexcept { return std::move(*this).value(); }
    const value_type* operator->() const noexcept { return std::addressof(value()); }

    const E& error() const& noexcept
    {
        bte::assert_true(!is_okay(), tokens::FatalExpectedErrorEmpty);
        return std::get<unexpected_type>(m_storage).value();
    }
    E&& error() && noexcept
    {
        bte::assert_true(!is_okay(), tokens::FatalExpectedErrorEmpty);
        return std::get<unexpected_type>(std::move(m_storage)).value();
    }

    template <class Fnc>
        auto and_then(Fnc&& f) const &
        noexcept -> decltype(std::invoke(f, std::declval<value_type>()))
    {
        if (is_okay())
        {
            return std::invoke(f, this->value());
        }
        else
        {
            return unexpected<error_type>(error());
        }
    }

    template <class Fnc>
        auto and_then(Fnc&& f) && noexcept -> decltype(std::invoke(f, std::declval<value_type>()))
    {
        if (is_okay())
        {
            return std::invoke(f, std::move(*this).value());
        }
        else
        {
            return unexpected<error_type>(std::move(*this).error());
        }
    }

    template <class Fnc>
        auto or_else(Fnc&& f) const &
        noexcept -> decltype(std::invoke(f, std::declval<error_type>()))
    {
        if (this->is_error())
        {
            return std::invoke(f, this->error());
        }
        else
        {
            return *this;
        }
    }

    template <class Fnc>
        auto or_else(Fnc&& f) && noexcept -> decltype(std::invoke(f, std::declval<error_type>()))
    {
        if (this->is_error())
        {
            return std::invoke(f, std::move(*this).error());
        }
        else
        {
            return std::move(*this);
        }
    }

private:
    std::variant<value_type, unexpected_type> m_storage;
};

template <class E>
class expected<void, E>
{
private:
    struct void_storage
    {
        constexpr void_storage() = default;
    };

public:
    using value_type      = void;
    using error_type      = E;
    using unexpected_type = unexpected<error_type>;

    expected() : m_storage(void_storage{}) {}
    expected(std::nullptr_t) : m_storage(void_storage{}) {}
    expected(const unexpected_type& e) noexcept : m_storage(e) {}
    expected(unexpected_type&& e) noexcept : m_storage(std::move(e)) {}

    template <class... Args>
    explicit expected(std::in_place_t) : expected<void, E>()
    {}

    expected<void, E>& operator=(const unexpected_type& other) noexcept
    {
        m_storage = other;
        return *this;
    }

    expected<void, E>& operator=(unexpected_type&& other) noexcept
    {
        m_storage = std::move(other);
        return *this;
    }

    bool is_okay() const noexcept
    {
        auto has_value = std::get_if<void_storage>(&m_storage) != nullptr;
        auto has_error = std::get_if<unexpected_type>(&m_storage) != nullptr;

        bte::assert_true(has_value ^ has_error, tokens::FatalExpectedInBadState);
        return has_value;
    }
    operator bool() const noexcept { return is_okay(); }

    const E& error() const& noexcept
    {
        bte::assert_true(!is_okay(), tokens::FatalExpectedErrorEmpty);
        return std::get<unexpected_type>(m_storage).value();
    }
    E&& error() && noexcept
    {
        bte::assert_true(!is_okay(), tokens::FatalExpectedErrorEmpty);
        return std::get<unexpected_type>(std::move(m_storage)).value();
    }

    template <class Fnc>
        auto and_then(Fnc&& f) const & noexcept -> decltype(std::invoke(f))
    {
        if (is_okay())
        {
            return std::invoke(f);
        }
        else
        {
            return unexpected<error_type>(error());
        }
    }

    template <class Fnc>
        auto and_then(Fnc&& f) && noexcept -> decltype(std::invoke(f))
    {
        if (is_okay())
        {
            return std::invoke(f);
        }
        else
        {
            return unexpected<error_type>(std::move(*this).error());
        }
    }

    template <class Fnc>
        auto or_else(Fnc&& f) const &
        noexcept -> decltype(std::invoke(f, std::declval<error_type>()))
    {
        if (this->is_error())
        {
            return std::invoke(f, error());
        }
        else
        {
            return *this;
        }
    }

    template <class Fnc>
        auto or_else(Fnc&& f) && noexcept -> decltype(std::invoke(f, std::declval<error_type>()))
    {
        if (this->is_error())
        {
            return std::invoke(f, std::move(*this).error());
        }
        else
        {
            return std::move(*this);
        }
    }

private:
    std::variant<void_storage, unexpected_type> m_storage;
};
}  // namespace bte_experimental