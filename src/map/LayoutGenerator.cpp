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

#include <stdexcept>
#include <algorithm>
#include <boost/assert.hpp>

#include "LayoutGenerator.hpp"

namespace airball
{
namespace map
{

LayoutGenerator::LayoutGenerator() : generator(randomDevice())
{
}

std::pair<Coordinates, LevelLayout> LayoutGenerator::generateDrunkDwarf(
    unsigned width, unsigned height, float fillPercentage)
{
    BOOST_ASSERT_MSG(width > 2, "generateDrunkDwarf: too small width");
    BOOST_ASSERT_MSG(height > 2, "generateDrunkDwarf: too small height");

    int tilesLeft = width * height * fillPercentage;

    LevelLayout layout(width, std::vector<Tile>(height, Tile("wall.png", true)));

    // We'll NEVER generate coordinates on a given border
    Coordinates origCoord =
        generateRandomCoordinates(1, std::max(1u, width - 2), 1, std::max(1u, height - 2));
    changeTileToFloor(origCoord, layout, tilesLeft);

    Coordinates coord = origCoord;

    while (tilesLeft > 0)
    {
        Coordinates toChange = coord + generateRandomCoordinates(-1, 1, -1, 1);
        if (changeTileToFloor(toChange, layout, tilesLeft))
        {
            coord = toChange;
        }
    }


    return std::make_pair(origCoord, layout);
}

bool LayoutGenerator::changeTileToFloor(const Coordinates& coord, LevelLayout& layout,
    int& tilesLeft) const
{
    try
    {
        Tile& tile = layout.at(coord.x).at(coord.y);
        size_t layoutHeight = layout[coord.x].size();
        if (coord.x > 0 && coord.x < static_cast<int>(layout.size() - 1) &&
            coord.y > 0 && coord.y < static_cast<int>(layoutHeight - 1))
        {
            if (tile.isObstacle())
            {
                tile = Tile("floor.png", false);
                --tilesLeft;
            }
            return true;
        }
    }
    catch(const std::out_of_range&)
    {
    }

    return false;
}

Coordinates LayoutGenerator::generateRandomCoordinates(
    int xStart, int xStop, int yStart, int yStop)

{
    std::uniform_int_distribution<int> xDis(xStart, xStop);
    std::uniform_int_distribution<int> yDis(yStart, yStop);

    int coordX = xDis(generator);
    int coordY = yDis(generator);

    return Coordinates(coordX, coordY);
}

} // namespace map
} // namespace airball
