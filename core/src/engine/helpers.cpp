#include "helpers.hpp"
#include <algorithm>

namespace bte {
namespace helpers {
struct RefEqComparator
{
    RefEqComparator(const Node& port) : m_port(port) {}

    bool operator()(const Connection& p) { return &p.port() == &m_port; }

private:
    const Node& m_port;
};

const Node* find_connection(const Node& parent, const Connections& connections)
{
    const Node* sub_tree = nullptr;

    if (connections.size() > 0)
    {
        auto it = std::find_if(&connections.begin(), &connections.end(), RefEqComparator(parent));

        if (it != &connections.end())
        {
            sub_tree = &it->node();
        }
    }

    return sub_tree;
}

//
// bits
// msb                                 lsb
// eepp pppp pppp pppp pccc cccc cccc cccc
//

std::uint32_t package_for_trace(std::size_t engine_id, const Node& meta_node, const Node* parent)
{
    uint8_t   buffer[sizeof(uint32_t)] = {0};
    uint32_t* id                       = reinterpret_cast<uint32_t*>(buffer);

    *id = ((0x03 & engine_id) << 30) | ((0x7FFF & (std::size_t)parent) << 15) |
          (0x7FFF & ((std::size_t)&meta_node));
    uint32_t* package = (reinterpret_cast<uint32_t*>(buffer));
    return *package;
}

NodeRefComparator::NodeRefComparator(const Node* node) : m_node(node) {}

bool NodeRefComparator::operator()(const Node* compare) { return compare == m_node; }
}  // namespace helpers
}  // namespace bte