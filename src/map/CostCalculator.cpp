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

#include <algorithm>
#include <limits>

#include "detail/Utils.hpp"

#include "CostCalculator.hpp"

namespace airball
{
namespace map
{

const int CostCalculator::OBSTACLE_COST = std::numeric_limits<int>::max();

CostMap CostCalculator::calculate(const GoalList& goals, const GoalList& obstacles,
    const LevelLayout& layout) const
{
    UNUSED_PARAM(goals);

    CostMap ret = createEmptyCostMap(layout);
    addObstacles(obstacles, ret);

    return ret;
}

CostMap CostCalculator::createEmptyCostMap(const LevelLayout& layout) const
{
    CostMap ret;

    for(const std::vector<Tile>& tileVector : layout)
    {
        std::vector<int> costColumn;
        std::transform(tileVector.begin(), tileVector.end(), std::back_inserter(costColumn),
            &CostCalculator::getTileCost);
        ret.push_back(std::move(costColumn));
    }

    return ret;
}


void CostCalculator::addObstacles(const GoalList& obstacles, CostMap& currentMap) const
{
    for (const Coordinates& coord : obstacles)
    {
        if (coord.inBoundaries(currentMap))
        {
            currentMap[coord.x][coord.y] = OBSTACLE_COST;
        }
    }
}

int CostCalculator::getTileCost(const Tile& tile)
{
    if (tile.isObstacle())
    {
        return OBSTACLE_COST;
    }
    return tile.moveFactor();
}

} // namespace map
} // namespace airball

