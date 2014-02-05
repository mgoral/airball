/**
 * Copyright (C) Michal Goral, 2014
 *
 * Airball is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Airball is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Airball; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef AIRBALL_GAME_COORDINATES_HPP_
#define AIRBALL_GAME_COORDINATES_HPP_

namespace game
{

struct Coordinates
{
    Coordinates(unsigned x, unsigned y) : x(x), y(y)
    {
    }

    unsigned x;
    unsigned y;
};

} // namespace game

#endif // AIRBALL_GAME_COORDINATES_HPP_
