/**
 * Copyright (C) Michal Goral, 2014
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef AIRBALL_MAP_DETAIL_GRAPHNOSED_HPP_
#define AIRBALL_MAP_DETAIL_GRAPHNOSED_HPP_

#include <memory>
#include <limits>
#include <boost/functional/hash.hpp>

#include "map/Coordinates.hpp"

namespace airball
{
namespace map
{
namespace detail
{

class Node;
typedef std::shared_ptr<Node> NodePtr;
typedef std::shared_ptr<const Node> NodeCPtr;

class HeapNode;
typedef std::shared_ptr<HeapNode> HeapNodePtr;

enum NodeState
{
    NodeStateOpen = 1,
    NodeStateClosed = 2,
    NodeStateNotVisited = 3
};

class Node
{
public:
    explicit Node(const Coordinates& coord) : coord_(coord)
    {
    }

    // Coordinates mustn't be changed
    const Coordinates& coordinates() const
    {
        return coord_;
    }

    void addNeighbour(const std::shared_ptr<Node>& node)
    {
        if (node)
            neighbours_.push_back(node);
    }

    const std::vector<NodePtr>& neighbours() const
    {
        return neighbours_;
    }

private:
    Coordinates coord_;
    std::vector<NodePtr> neighbours_;
};

bool operator==(const Node& lhs, const Node& rhs);
bool operator<(const Node& lhs, const Node& rhs);
std::size_t hash_value(const Node& node);
std::size_t hash_value(const NodeCPtr& nodePtr);

/**
 * A structure represented in max-heap.
 * NOTE: because HeapNode is to be stored in max-heap (and A* algorithm requires min-heap),
 * operator<() of it returns opposite value (i.e. operator<(lhs, hrs) returns bool(lhs > rhs)).
 */
class HeapNode
{
public:
    explicit HeapNode(const NodeCPtr& node) :
        node_(node),
        state_(NodeStateNotVisited),
        distance_(std::numeric_limits<unsigned>::max()),
        cost_(std::numeric_limits<unsigned>::max())
    {
    }

    NodeCPtr node() const
    {
        return node_;
    }

    void setParent(const HeapNodePtr& parent)
    {
        if (parent)
            parent_ = parent;
    }

    /**
     * If HeapNode doesn't have a parent, it is set to empty shared_ptr.
     */
    HeapNodePtr parent() const
    {
        return parent_;
    }

    void setState(NodeState state)
    {
        state_ = state;
    }

    NodeState state() const
    {
        return state_;
    }

    void setDistance(unsigned distance)
    {
        distance_ = distance;
    }

    unsigned distance() const
    {
        return distance_;
    }

    void setCost(unsigned cost)
    {
        cost_ = cost;
    }

    unsigned cost() const
    {
        return cost_;
    }

private:
    NodeCPtr node_;
    HeapNodePtr parent_;
    NodeState state_;

    unsigned distance_;
    unsigned cost_;
};

bool operator==(const HeapNode& lhs, const HeapNode& rhs);
bool operator<(const HeapNode& lhs, const HeapNode& rhs);
bool operator<(const HeapNodePtr& lhs, const HeapNodePtr& rhs);

} // namespace detail
} // namespace map
} // namespace airball


#endif // AIRBALL_MAP_DETAIL_GRAPHNOSED_HPP_
