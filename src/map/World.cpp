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

#include "World.hpp"

#include "components/Description.hpp"
#include "components/Animation.hpp"

namespace airball
{
namespace map
{

components::Description playerDescriptionFactory()
{
    components::Description descr;
    descr.image = "player.png";
    descr.player = true;
    descr.obstacle = true;
    descr.creature = true;

    return descr;
}

void setObjectAnimation(map::SharedObjectPtr& object)
{
    components::Animation anim(8);

    SDL_Rect source = {
        static_cast<int>(map::Object::size()) * object->coordinates().x,
        static_cast<int>(map::Object::size()) * object->coordinates().y,
        static_cast<int>(map::Object::size()),
        static_cast<int>(map::Object::size())
    };

    SDL_Rect destination = {
        static_cast<int>(map::Object::size()) * object->coordinates().x,
        static_cast<int>(map::Object::size()) * object->coordinates().y,
        static_cast<int>(map::Object::size()),
        static_cast<int>(map::Object::size())
    };

    anim.reset();
    anim.setMovementSource(source);
    anim.setMovementDestination(destination);
    object->addComponent(anim);
}

World::World() : currentLevelUuid_(0)
{
    Coordinates freeCoordinates = createLevel();
    Level& firstLevel = levels_.back();
    changeCurrentLevel(firstLevel);

    // TODO: objects factory (with uuid assigner)
    map::SharedObjectPtr futurePlayer =
        std::make_shared<map::Object>(freeCoordinates, playerDescriptionFactory(), 0);
    setObjectAnimation(futurePlayer);

    if (firstLevel.addObject(futurePlayer))
    {
        std::vector<map::SharedCObjectPtr> objects = firstLevel.objectsAt(freeCoordinates);
        player_ = objects[0];
    }
    else
    {
        throw std::logic_error("Cannot create player on the level");
    }
}

Coordinates World::createLevel()
{
    unsigned uuid = levels_.size();
    unsigned width = 60;
    unsigned height = 32;

    std::pair<Coordinates, LevelLayout> genRet = generator_.generateDrunkDwarf(width, height);
    levels_.emplace_back(std::move(genRet.second), uuid);

    return genRet.first;
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

const SharedCObjectPtr& World::player() const
{
    return player_;
}

} // namespace map
} // namespace airball
