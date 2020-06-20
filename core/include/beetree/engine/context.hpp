///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/btos/optional.hpp"
#include "beetree/engine/exception.hpp"
#include "beetree/engine/node.hpp"

namespace bte {

class Builder;  // forward delcaration

/// The Context provided to each node's setup, loop, teardown, etc. The
/// context provides the corresponding node, state, and other pertinent
/// information
struct Context
{
public:
    // > Constructors
    Context() = default;
    Context(const Node& n, const optional<Exception>& ex, uint8_t* d, std::size_t l)
        : m_node(&n), m_cur_exception(ex), m_data(d), m_len(l)
    {}

    /// @return the compile time node
    const Node& get_node() const { return *m_node; }

    /// @return the run-time node's internal data
    template <class T>
    T* get_data()
    {
        return reinterpret_cast<T*>(m_data);
    }

    /// @return if in a catch node, the tree's current exception.
    optional<Exception> get_cur_exception() const { return m_cur_exception; }

private:
    friend class Builder;
    const Node*         m_node = nullptr;
    optional<Exception> m_cur_exception{nullopt};
    uint8_t*            m_data = nullptr;
    std::size_t         m_len  = 0;
};
}  // namespace bte
