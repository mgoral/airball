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

#ifndef AIRBALL_RENDERABLE_HPP_
#define AIRBALL_RENDERABLE_HPP_

#include <string>
#include <SDL2/SDL.h>

namespace airball
{

class Renderable
{
public:
    /**
     * Returns image name that should be rendered (e.g. 'image.png').
     */
    virtual std::string imageName() const = 0;

    /**
     * Returns a part of image that should be rendered (e.g. when a single image contains several
     * object states). If whole image should be rendered, a nullptr is returned (default
     * implementation).
     */
    virtual SDL_Rect* getImagePart() const
    {
        return nullptr;
    }
};

} // namespace airball

#endif // AIRBALL_RENDERABLE_HPP_
