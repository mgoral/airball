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

#ifndef AIRBALL_SCREEN_HPP_
#define AIRBALL_SCREEN_HPP_

#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>

#include "Logger.hpp"
#include "Renderable.hpp"

namespace airball
{

class VideoError : public std::runtime_error
{
public:
    explicit VideoError(const std::string& what) : std::runtime_error(what)
    {
    }

    explicit VideoError(const char* what) : std::runtime_error(what)
    {
    }
};

class Screen
{
public:
    Screen(int width, int height, bool fullscreen);
    Screen(int width, int height);
    ~Screen();

    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;

    void update() const;

    void addRenderable(const Renderable& renderable, SDL_Rect* destination);
    void clear();

private:
    SDL_Window* initWindow(int width, int height, bool fullscreen);
    SDL_Renderer* initRenderer();

private:
    airball::Logger logger_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
};

} // namespace airball

#endif // AIRBALL_SCREEN_HPP_
