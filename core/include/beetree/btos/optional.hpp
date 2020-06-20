//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <utility>

namespace bte {

struct nullopt_t
{    
    explicit constexpr nullopt_t() = default;
};

constexpr nullopt_t nullopt{};

///
/// The optional class is a naive mirror of c++ 17's std::optional<T> class. This implementation
/// does not support emplace operations nor initializer lists.
template <class T>
class optional
{
public:
    using value_type = T;

    // constructors
    constexpr optional() noexcept : m_value(), m_has_value(false){};
    constexpr optional(nullopt_t) : m_value(), m_has_value(false){};

    template <class U = T>
    constexpr optional(U&& value) : m_value(static_cast<T>(std::forward<U>(value))), m_has_value(true){};

    template <class U = T>
    constexpr optional(const optional<U>& cpy) : m_value(static_cast<T>(cpy.m_value)), m_has_value(cpy.m_has_value)
    {}

    template <class U = T>
    constexpr optional(optional<U>&& mv)
        : m_value(std::move(static_cast<T>(mv.m_value))), m_has_value(mv.m_has_value)
    {
        // the moved optional still contains a value, but the value's state is moved
        // so do not modify the 'mv's m_has_value
    }

    // destructor
    ~optional() = default;

    // swap
    void swap(optional<T>& other) noexcept
    {
        std::swap(this->m_value, other.m_value);
        std::swap(this->m_has_value, other.m_has_value);
    }

    // observers
    constexpr const T* operator->() const { return &m_value; }
    T*                 operator->() { return &m_value; }

    constexpr const T& operator*() const { return m_value; }
    T&                 operator*() { return m_value; }

    constexpr explicit operator bool() const noexcept { return m_has_value; }

    constexpr bool has_value() const noexcept { return m_has_value; }

    constexpr const T& value() const { return m_value; }
    T&                 value() { return m_value; }

    template <class U>
    constexpr T value_or(U&& default_value) const
    {
        return m_has_value ? m_value : static_cast<T>(std::forward<U>(default_value));
    }

    template <class U>
    T value_or(U&& default_value)
    {
        return m_has_value ? std::move(m_value) : static_cast<T>(std::forward<U>(default_value));
    }

    // modifiers
    void reset() noexcept
    {
        m_value     = T{};
        m_has_value = false;
    }

private:
    T    m_value{};
    bool m_has_value{false};
};

template <class T>
void swap(optional<T>& lhs, optional<T>& rhs) noexcept
{
    lhs.swap(rhs);
}

}  // namespace bte