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

#ifndef AIRBALL_MAP_ACTIONS_HPP
#define AIRBALL_MAP_ACTIONS_HPP

#include "IAction.hpp"

#include "World.hpp"
#include "Level.hpp"
#include "Object.hpp"
#include "Coordinates.hpp"

namespace airball
{
namespace map
{

class MoveAction : public IAction
{
public:
    MoveAction(World& world, SharedCObjectPtr object, const Coordinates& direction) :
        world_(world), object_(object), direction_(direction)
    {
    }

    void run()
    {
        Level& level = world_.currentLevel();

        Coordinates destination = object_->coordinates() + direction_;
        Coordinates dimensions = level.dimensions();

        destination.x = std::max(0, destination.x);
        destination.x = std::min(dimensions.x - 1, destination.x);
        destination.y = std::max(0, destination.y);
        destination.y = std::min(dimensions.y - 1, destination.y);

        level.moveObject(object_, destination);
    }

private:
    World& world_;
    SharedCObjectPtr object_;
    Coordinates direction_;
};

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_ACTIONS_HPP
