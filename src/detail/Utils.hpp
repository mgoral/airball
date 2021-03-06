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

#ifndef AIRBALL_UTILS_HPP_
#define AIRBALL_UTILS_HPP_

/**
 * Miscellaneous utilities used anywhere in the project
 */

#include <SDL2/SDL.h>
#include "map/Coordinates.hpp"

// A little trick to get rid of compiler errors when there are unused parameters.
// Helpful when e.g. 'ifndef NDEBUG' removes usage of said parameter.
#define UNUSED_PARAM(x) (void)(x)

namespace airball
{
namespace detail
{

// Simple converters from coordinates to SDL_Rect
SDL_Rect coord2Rect(const airball::map::Coordinates& coord, unsigned sizeFactor);

} // namespace detail
} // namespace airball

#endif // AIRBALL_UTILS_HPP_
