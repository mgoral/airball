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

#ifndef AIRBALL_MAP_WORLD_HPP_
#define AIRBALL_MAP_WORLD_HPP_

#include <vector>

#include "Level.hpp"
#include "LayoutGenerator.hpp"

namespace airball
{
namespace map
{

class World
{
public:
    World();

    /**
     * Returns a randomly picked non-obstacle coordinates on created level
     */
    Coordinates createLevel();
    Level& currentLevel();
    void changeCurrentLevel(const Level& level);
    Level& level(unsigned uuid);

    SharedCObjectPtr player() const;

private:
    std::vector<Level> levels_;
    unsigned currentLevelUuid_;
    SharedCObjectPtr player_;
    LayoutGenerator generator_;
};

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_WORLD_HPP_
