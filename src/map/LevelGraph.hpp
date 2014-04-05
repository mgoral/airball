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

#ifndef AIRBALL_MAP_LEVELGRAPH_HPP_
#define AIRBALL_MAP_LEVELGRAPH_HPP_

#include <vector>
#include <map>
#include <unordered_map>

#include "MapTypes.hpp"
#include "Coordinates.hpp"

#include "detail/GraphNodes.hpp"

namespace airball
{
namespace map
{

class LevelGraph
{
private:
    using Node = airball::map::detail::Node;
    using NodePtr = airball::map::detail::NodePtr;
    using NodeCPtr = airball::map::detail::NodeCPtr;

    using HeapNode = airball::map::detail::HeapNode;
    using HeapNodePtr = airball::map::detail::HeapNodePtr;

    using SearchMap = std::unordered_map<NodeCPtr, HeapNodePtr, boost::hash<NodeCPtr>>;
    using SearchMapRet = std::pair<SearchMap::iterator, bool>;

    typedef std::map<Coordinates, NodePtr> NodeMap;

public:
    explicit LevelGraph(const LevelLayout& layout);

    void reset(const LevelLayout& layout);

    /**
     * Shortest path search algorithms.
     * Return found path. If there is no path from 'from' to 'to', returned Path is empty.
     */
    Path findPath(const Coordinates& from, const Coordinates& to, const CostMap& costMap) const;
    Path findDijkstraPath(const Coordinates& from, const Coordinates& to,
        const CostMap& costMap) const;

private:
    NodePtr& insertNode(const Coordinates& coord, const NodePtr& node);
    void addNode(int x, int y, const LevelLayout& layout);
    void addNodeNeighbours(const LevelLayout& layout, NodePtr& node);
    const NodePtr& findNode(const Coordinates& coord) const;

    template <typename HeuristicFunc>
    Path findPath(const NodePtr& from, const NodePtr& to, const CostMap& costMap,
        HeuristicFunc heuristic) const;
    Path recreatePath(const NodePtr& goalNode, SearchMap& searchMap) const;
    HeapNodePtr insertNodeToSearchMap(const NodeCPtr&, SearchMap& searchMap) const;

    // A* heuristics
    static unsigned diagonalShortcutHeuristic(const NodeCPtr& node, const NodeCPtr& start,
        const NodeCPtr& goal);
    static unsigned manhattanHeuristic(const NodeCPtr& node, const NodeCPtr& start,
        const NodeCPtr& goal);
    static unsigned dijkstraHeuristic(const NodeCPtr& node, const NodeCPtr& start,
        const NodeCPtr& goal);

    // A* priority compare
    /*
    bool costCompare(unsigned lhs, unsigned rhs, const std::vector<HeapNode>& nodes)
    {
        return (nodes[lhs] < nodes[rhs]);
    }
    */

private:
    NodeMap graph_;
};

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_LEVELGRAPH_HPP_
