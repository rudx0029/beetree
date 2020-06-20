#pragma once

#include <cstdint>
#include "beetree/engine/connections.hpp"
#include "beetree/engine/node.hpp"

namespace bte {
namespace helpers {
const Node* find_connection(const Node& parent, const Connections& connections);

const Node* get_decorator_child(const Node& parent);

std::uint32_t package_for_trace(std::size_t engine_id, const Node& meta_node, const Node* parent);

struct NodeRefComparator
{
    NodeRefComparator(const Node* node);
    bool operator()(const Node* compare);

private:
    const Node* m_node;
};

}  // namespace helpers
}  // namespace bte