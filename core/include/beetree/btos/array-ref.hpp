//------------------------------------------------------------------------------
// Copyright (C) 2021 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <optional>

namespace bte {

///
/// A type erased reference wrapper for std::array<T,N> and T array[N] with convenient indexing supporting
/// enumerations. 
///
/// Essentially its a std::reference_wrapper<std::array<T,N>> with the size `N` type erased.
/// bte::array_ref aligns itself with std::array except it returns std::optional<> where std::array
/// would throw an exception. 
///
/// The container internally references the data buffer of a std::array<T,N>. **Therefore the
/// lifetime of the reference can not be greater than the std::array<T,N> it references.**
///
/// The array_ref<T> is copyable and can be thought of as a reference to an array allocated else
/// where. This means the array_ref<T> can be returned directly and passed into a method directly.
/// For example,
///
/// ```cpp
///
/// array_ref<int> pass_through(array_ref<int> a)
/// {
///     return a;
/// }
///
/// void test()
/// {
///     int buffer[3] = {1,2,3};
///     auto items = array_ref{buffer};
///
///     auto result = pass_through(items);
///
///     auto items_it = items.begin();
///     auto result_it = result.begin();
///
///     for(int i = 0; i < 3; i++)
///     {
///         EXPECT_EQ(*items_it, *result_it);
///         items_it++;
///         result++;
///     }
/// }
/// ```
/// @tparam T the data type of the collection
///

template <class T>
class array_ref final
{
public:
    using value_type             = T;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /// [default] Constructs an invalid array_ref
    ///
    /// @see array_ref<T>::empty()
    array_ref() = default;

    /// Constructs the object from a pointer to a buffer
    ///
    /// @param data a pointer to the buffer to reference
    /// @param n number of items in the buffer
    array_ref(T* data, std::size_t n) : m_data(data), m_size(n) {}

    /// Constructs the object from a declared array.
    ///
    /// @tparam T the size of the array
    /// @param data the array to reference
    template <std::size_t N>
    array_ref(T (&data)[N]) : m_data(data), m_size(N)
    {}

    /// Constructs the object from a std::array<T,N>
    ///
    /// @tparam N the size of the array
    /// @param data the std::array to reference
    template <std::size_t N>
    array_ref(std::array<T, N>& data) : m_data(data.data()), m_size(data.size())
    {}

    /// @return the number of items in the container
    std::size_t size() const { return m_size; }

    /// @return a [const] reference to the beginning of the array
    /// @note the behavior is undefined if the array is empty
    T&       front() { return m_data[0]; }
    const T& front() const { return m_data[0]; }

    /// @return a [const] reference to the end of the array
    /// @note the behavior is undefined if the array is empty
    T&       back() { return m_data[m_size - 1]; }
    const T& back() const { return m_data[m_size - 1]; }

    /// @return a pointer to the underlying array buffer;
    T*       data() { return m_data; }
    const T* data() const { return m_data; }

    /// @return true when the underlying array is invalid or when the array has 0 size.
    /// @return false otherwise
    bool empty() const { return m_data == nullptr || m_size == 0; }

    /// @return an iterator at the beginning of the collection, i.e. array element 0
    iterator begin() { return !empty() ? &m_data[0] : end(); }

    /// @return a const iterator at the beginning of the collection, i.e. array element 0
    const_iterator begin() const { return !empty() ? &m_data[0] : end(); }

    /// @return a const iterator at the beginning of the collection, i.e. array element 0
    const_iterator cbegin() const { return !empty() ? &m_data[0] : end(); }

    /// @return an iterator marking the end of the collection, i.e. array element N + 1
    iterator end() { return !empty() ? &m_data[size()] : nullptr; }

    /// @return a const iterator marking the end of the collection, i.e. array element N + 1
    const_iterator end() const { return !empty() ? &m_data[size()] : nullptr; }

    /// @return a const iterator marking the end of the collection, i.e. array element N + 1
    const_iterator cend() const { return !empty() ? &m_data[size()] : nullptr; }

    /// Gets an immutable reference to the item at the given index with bounds checking
    ///
    /// @tparam Index an enumeration type or an unsigned integer type
    /// @param index the index of the item to get
    /// @return std::optional<std::reference_wrapper<const T>> when the array_ref<T> is not empty
    /// @return std::nullopt when the array_ref<T> is empty.
    template <class Index = std::size_t,
              class I     = std::conditional_t<std::is_enum_v<Index>, std::size_t, Index>>
    std::optional<std::reference_wrapper<const T>> at(Index index) const
    {
        static_assert(std::is_unsigned_v<I>, "Index type is not an enum or unsigned");

        auto i = static_cast<I>(index);
        if (empty() || i >= size())
        {
            return std::nullopt;
        }
        else
        {
            return std::make_optional(std::cref(m_data[i]));
        }
    }

    /// Gets an mutable reference to the item at the given index with bounds checking
    ///
    /// @tparam Index an enumeration type or an unsigned integer type
    /// @param index the index of the item to get
    /// @return std::optional<std::reference_wrapper<T>>  when the array_ref<T> is not empty
    /// @return std::nullopt when the array_ref<T> is empty.
    template <class Index = std::size_t,
              class I     = std::conditional_t<std::is_enum_v<Index>, std::size_t, Index>>
    std::optional<std::reference_wrapper<T>> at(Index index)
    {
        static_assert(std::is_unsigned_v<I>, "Index type is not an enum or unsigned");

        auto i = static_cast<I>(index);
        if (empty() || i >= size())
        {
            return std::nullopt;
        }
        else
        {
            return std::make_optional(std::ref(m_data[i]));
        }
    }

    /// Gets an immutable reference to the item at the given index with no bounds checking
    ///
    /// @note The behavior is undefined if the array is empty or the index is out of range
    ///
    /// @tparam Index an enumeration type or an unsigned integer type
    /// @param index the index of the item to get
    /// @return the immutable item at the given index
    template <class Index = std::size_t,
              class I     = std::conditional_t<std::is_enum_v<Index>, std::size_t, Index>>
    const T& operator[](Index index) const
    {
        static_assert(std::is_unsigned_v<I>, "Index type is not an enum or unsigned");
        auto i = static_cast<I>(index);
        return m_data[i];
    }

    /// Gets an mutable reference to the item at the given index with no bounds checking
    ///
    /// @note The behavior is undefined if the array is empty or the index is out of range
    ///
    /// @tparam Index an enumeration type or an unsigned integer type
    /// @param index the index of the item to get
    /// @return the mutable item at the given index
    template <class Index = std::size_t,
              class I     = std::conditional_t<std::is_enum_v<Index>, std::size_t, Index>>
    T& operator[](Index index)
    {
        static_assert(std::is_unsigned_v<I>, "Index type is not an enum or unsigned");
        auto i = static_cast<I>(index);
        return m_data[i];
    }

private:
    pointer     m_data{nullptr};
    std::size_t m_size = 0;
};

///
/// Converts an array_ref<T>::const_iterator to an index relative to begin().
///
/// @param arr the iterator's array_ref
/// @param it the iterator to convert to an index
/// @return std::optional<std::size_t> containing the index
/// @return std::nullopt when the array_ref or iterator is not valid
///
template <class T>
std::optional<std::size_t> to_index(const array_ref<T>&                   arr,
                                    typename array_ref<T>::const_iterator it)
{
    std::optional<std::size_t> idx = std::nullopt;
    if (!arr.empty() && it >= arr.begin() && it < arr.end())
    {
        idx = it - arr.begin();
    }
    return idx;
}
}  // namespace bte
