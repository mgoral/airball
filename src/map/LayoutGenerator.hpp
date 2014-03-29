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

#ifndef AIRBALL_MAP_LAYOUTGENERATOR_HPP_
#define AIRBALL_MAP_LAYOUTGENERATOR_HPP_

#include <vector>
#include <random>

#include "Tile.hpp"
#include "Coordinates.hpp"

namespace airball
{
namespace map
{

typedef std::vector<std::vector<Tile>> LevelLayout;

class LayoutGenerator
{
public:
    LayoutGenerator();

    /**
     * Drunk Dwarf algorithm. Selects a random coordinates and starts digging in random directions.
     * Depending on fillPercentage usually results in cave-like system with some narrow corridors.
     *
     * Returns a created level with coordinates of randomly picked non-obstacle tile.
     */
    std::pair<Coordinates, LevelLayout> generateDrunkDwarf(
        unsigned width, unsigned height, float fillPercentage = 0.3);

private:
    /**
     * Changes a obstacle tile at given coordinates to non-obstacle floor. All tiles but level
     * border can be changed. 
     * Returns whether tile after function call is floor or not
     */
    bool changeTileToFloor(const Coordinates& coord, LevelLayout& layout, int& tilesLeft) const;
    Coordinates generateRandomCoordinates(int xStart, int xStop, int yStart, int yStop);

private:
    std::random_device randomDevice;
    std::mt19937_64 generator;
};

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_LAYOUTGENERATOR_HPP_
