///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------
#pragma once

#include "beetree/engine/node.hpp"

namespace bte {
/// Allows a tree to define a 'hanging node' or port such that a node can be
/// paired with the tree at a later time. This is advantageous when a tree
/// wishes to support behaviors not specified in the tree; a type of late
/// binding.
struct Connection
{
    // > Properties
    constexpr const Node& port() const { return *m_port; }
    constexpr const Node& node() const { return *m_node; }

    // > Constructors
    constexpr Connection(const Node& port, const Node& node) : m_port(&port), m_node(&node) {}

private:
    const Node* m_port = nullptr;
    const Node* m_node = nullptr;
};

// > collection

/// A fixed-sized, constant expression array of connections
template <std::size_t N>
struct ConnectionArray final
{
    constexpr std::size_t size() const { return N; }
    Connection            array[N];
};

// > make connections

/// Creates a constant expression array of connections. This allows the
/// connections to be written to 'FLASH' rather than in 'RAM'
template <typename... Args>
static constexpr auto pin_connections(const Args&... values) -> ConnectionArray<sizeof...(Args)>
{
    return ConnectionArray<sizeof...(Args)>{values...};
}

/// Connections container to be consumed by the engine
struct Connections
{
public:
    // > accessors and iterators
    std::size_t       size() const { return m_size; }
    const Connection& begin() const { return m_array[0]; }
    const Connection& end() const { return m_array[m_size]; }
    const Connection& operator[](std::size_t i) const { return m_array[i]; }

    // > constructors
    constexpr Connections() = default;

    template <std::size_t N>
    constexpr Connections(const ConnectionArray<N>& connections)
        : Connections(connections.array, connections.size())
    {}

    constexpr Connections(const Connection* array, std::size_t num_connections)
        : m_array(array), m_size(num_connections)
    {}

private:
    const Connection* m_array = nullptr;
    std::size_t       m_size  = 0;
};
}  // namespace bte