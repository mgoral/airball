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
    MoveAction(map::Level& level, map::SharedCObjectPtr& player,
        const map::Coordinates& direction) :
            level_(level), player_(player), direction_(direction)
    {
    }

    void run()
    {
        map::Coordinates destination = player_->coordinates() + direction_;
        map::Coordinates dimensions = level_.dimensions();

        destination.x = std::max(0, destination.x);
        destination.x = std::min(dimensions.x - 1, destination.x);
        destination.y = std::max(0, destination.y);
        destination.y = std::min(dimensions.y - 1, destination.y);

        level_.moveObject(player_, destination);
    }

private:
    map::Level& level_;
    map::SharedCObjectPtr player_;
    map::Coordinates direction_;
};

} // namespace states
} // namespace airball

#endif // AIRBALL_STATES_GAMESTATEACTIONS_HPP_
