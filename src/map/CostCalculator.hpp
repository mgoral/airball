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

// Big thanks go to Brian Walker (Brogue developer - check it out) for this article:
// http://www.roguebasin.com/index.php?title=The_Incredible_Power_of_Dijkstra_Maps

#ifndef AIRBALL_MAP_COSCALCULATOR_HPP_
#define AIRBALL_MAP_COSCALCULATOR_HPP_

#include <vector>

#include "MapTypes.hpp"
#include "Level.hpp"
#include "Coordinates.hpp"

namespace airball
{
namespace map
{

class CostCalculator
{
public:
    CostMap calculate(const GoalList& goals, const GoalList& obstacles,
        const LevelLayout& layout) const;

private:
    CostMap createEmptyCostMap(const LevelLayout& layout) const;
    void addObstacles(const GoalList& obstacles, CostMap& currentMap) const;

    static int getTileCost(const Tile& tile);

private:
    static const int OBSTACLE_COST;
};

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_COSCALCULATOR_HPP_
