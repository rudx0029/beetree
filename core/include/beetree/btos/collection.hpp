//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <cstdint>
#include "beetree/btos/optional.hpp"

namespace bte {

///
/// A generic, iterable, read-only container of T type items.
///
/// The container internally references a memory aligned buffer or array. **Therefore the lifetime
/// of the Collection can not be greater than the buffer it references.**
///
/// The Collection is copyable and can be thought of as a reference to an array allocated else
/// where. This means the Collection can be returned directly and passed into a method directly.
/// For example,
///
/// ```cpp
/// int buffer[3] = {1,2,3};
/// Container<int> items{buffer, 3};
///
/// Container<int> pass_through(Container<int> a)
/// {
///     return a;
/// }
///
/// void test()
/// {
///     int buffer[3] = {1,2,3};
///     Container<int> items{buffer, 3};
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
///         resutlit++;
///     }
/// }
/// ```
/// @tparam T the data type of the collection
///
template <class T>
class Collection final
{
public:
    using iterator                    = T*;
    using const_iterator              = const T*;
    static constexpr T* null_iterator = nullptr;

    Collection() = default;
    Collection(T* items, std::size_t num_items) : m_items(items), m_num_items(num_items) {}

    /// @return the number of items in the container
    std::size_t size() const { return m_num_items; }
    /// @return true when the collection has a valid buffer with a size greater than 0.
    bool is_valid() const { return m_items != nullptr && size() > 0; }

    /// @return an iterator at the beginning of the collection, i.e. array element 0
    iterator begin() { return is_valid() ? &m_items[0] : end(); }
    /// @return a const iterator at the beginning of the collection, i.e. array element 0
    const_iterator begin() const { return is_valid() ? &m_items[0] : end(); }

    /// @return an iterator marking the end of the collection, i.e. array element N + 1
    iterator end() { return is_valid() ? &m_items[size()] : nullptr; }
    /// @return a const iterator marking the end of the collection, i.e. array element N + 1
    const_iterator end() const { return is_valid() ? &m_items[size()] : nullptr; }

    //----------------------
    // Extension Methods
    //----------------------

    ///
    /// Converts an iterator to an index relative to begin().
    ///
    /// @param collection the iterator's collection
    /// @param the iterator to convert to an index
    /// @return the index of the iterator or -1 if the collection or iterator is not valid
    ///
    static int32_t to_index(const Collection<T>& collection, const_iterator it)
    {
        int32_t idx = -1;
        if (collection.is_valid() && it >= collection.begin() && it < collection.end())
        {
            idx = it - collection.begin();
        }
        return idx;
    }

private:
    T*          m_items     = nullptr;
    std::size_t m_num_items = 0;
};

///
/// A collection that allocates its buffer internally.
///
/// The allocated collection is a convenience class for allocating the buffer internally with
/// implicit conversion to the read-only Collection. The examples below are equivalent in this
/// case and show that the AllocatedCollection takes the place of declaring the buffer. Collection
/// and AllocatedCollection should be used in tandem with one another, keeping in mind the any
/// instance of a Collection's lifetime must be within the lifetime of the AllocatedCollection.
///
/// ```cpp
/// Collection<int> from_buffer()
/// {
///     static int buffer[3];
///     return Collection<int>(buffer, 3);
/// }
///
/// Collection<int> from_allocated_collection()
/// {
///     static AllocatedCollection<int, 3> allocated;
///     return allocated; // okay since implicit cast will occur
///     // return allocated.to_collection(); -- okay as well
/// }
/// ```
///
///
/// @tparam T the data type of the collection
/// @tparam N the number of items in the collection to allocate
/// @tparam TIndexType the type used to index the collection defaulting to size_t. This is useful
/// when wanting to index with an enumeration to avoid static casting the enum to an integer. See
/// AllocatedCollection<T>::set and AllocatedCollection<T>::operator[]
///
template <class T, std::size_t N, class TIndexType = std::size_t>
class AllocatedCollection final
{
public:
    AllocatedCollection() {}

    ///
    /// Sets the item in the collection specified by the index `idx`.
    ///
    /// @param idx the index specifying wich item to modify.
    /// @param item the value to set the item to.
    ///
    void set(TIndexType idx, const T& item)
    {
        std::size_t i = static_cast<std::size_t>(idx);
        if (i < N)
        {
            m_items[i] = item;
        }
    }

    ///
    /// Sets/Gets the item specified by the index `idx`.
    ///
    /// > Use with care as there is no bounds checking on the index.
    ///
    /// @param idx the index specifying wich item to modify.
    /// @return a mutable reference to the item
    ///
    T& operator[](TIndexType idx) { return m_items[static_cast<std::size_t>(idx)]; }
    ///
    /// Gets the item specified by the index `idx`.
    ///
    /// > Use with care as there is no bounds checking on the index.
    ///
    /// @param idx the index specifying wich item to modify.
    /// @return a mutable reference to the item
    ///
    const T& operator[](TIndexType idx) const { return m_items[static_cast<std::size_t>(idx)]; }

    ///
    /// Returns the AllocatedCollection as the read-only, size-invariant,
    /// Collection.
    ///
    /// @note
    /// The lifetime of the return collection is the same as this allocated
    /// collection
    /// @endnote
    ///
    /// @return Collection<T>
    ///
    Collection<T> to_collection() { return {m_items, N}; }

    operator Collection<T>() { return to_collection(); }

private:
    T m_items[N] = {};
};
}  // namespace bte