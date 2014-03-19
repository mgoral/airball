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

#include "World.hpp"

namespace airball
{
namespace map
{

map::ObjectProperties playerPropertiesFactory()
{
    map::ObjectProperties prop;
    prop.image = "player.png";

    return prop;
}

World::World() : currentLevelUuid_(0)
{
    Level& firstLevel = createLevel();
    changeCurrentLevel(firstLevel);

    // TODO: objects factory (with uuid assigner)
    Coordinates playerCoordinates(0, 0);
    map::SharedCObjectPtr futurePlayer =
        std::make_shared<map::Object>(playerCoordinates, playerPropertiesFactory(), 0);
    if (firstLevel.addObject(futurePlayer))
    {
        std::vector<map::SharedCObjectPtr> objects = firstLevel.objectsAt(playerCoordinates);
        player_ = objects[0];
    }
    else
    {
        throw std::logic_error("Cannot create player on the level");
    }
}

Level& World::createLevel()
{
    unsigned uuid = levels_.size();
    unsigned width = 200;
    unsigned height = 100;

    levels_.emplace_back(width, height, uuid);
    return levels_.back();
}

Level& World::currentLevel()
{
    return levels_.at(currentLevelUuid_);
}

void World::changeCurrentLevel(const Level& level)
{
    currentLevelUuid_ = level.uuid();
}

Level& World::level(unsigned uuid)
{
    return levels_[uuid];
}

SharedCObjectPtr World::player() const
{
    return player_;
}

} // namespace map
} // namespace airball
