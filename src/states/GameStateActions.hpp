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

#ifndef AIRBALL_STATES_GAMESTATEACTIONS_HPP_
#define AIRBALL_STATES_GAMESTATEACTIONS_HPP_

#include "IAction.hpp"

#include "map/World.hpp"
#include "map/Level.hpp"
#include "map/Object.hpp"
#include "map/Coordinates.hpp"

namespace airball
{
namespace states
{

class MoveAction : public IAction
{
public:
    MoveAction(map::World& world, map::SharedCObjectPtr object, const map::Coordinates& direction) :
        world_(world), object_(object), direction_(direction)
    {
    }

    void run()
    {
        map::Level& level = world_.currentLevel();

        map::Coordinates destination = object_->coordinates() + direction_;
        map::Coordinates dimensions = level.dimensions();

        destination.x = std::max(0, destination.x);
        destination.x = std::min(dimensions.x - 1, destination.x);
        destination.y = std::max(0, destination.y);
        destination.y = std::min(dimensions.y - 1, destination.y);

        level.moveObject(object_, destination);
    }

private:
    map::World& world_;
    map::SharedCObjectPtr object_;
    map::Coordinates direction_;
};

} // namespace states
} // namespace airball

#endif // AIRBALL_STATES_GAMESTATEACTIONS_HPP_
