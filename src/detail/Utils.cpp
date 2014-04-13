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
 */

#include "Utils.hpp"

namespace airball
{
namespace detail
{

SDL_Rect coord2Rect(const airball::map::Coordinates& coord, unsigned sizeFactor)
{
    SDL_Rect ret = {
        static_cast<int>(sizeFactor) * coord.x,
        static_cast<int>(sizeFactor) * coord.y,
        static_cast<int>(sizeFactor),
        static_cast<int>(sizeFactor)
    };
    return ret;
}

} // namespace detail
} // namespace airball
