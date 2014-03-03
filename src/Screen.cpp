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

#include <SDL2/SDL.h>

#include "Screen.hpp"
#include "Translate.hpp"

namespace airball
{

Screen::Screen(int width, int height, bool fullscreen) :
    logger_(airball::LogCategoryVideo),
    window_(initWindow(width, height, fullscreen)),
    renderer_(initRenderer())
{
}

Screen::Screen(int width, int height) : Screen(width, height, false)
{
}

SDL_Window* Screen::initWindow(int width, int height, bool fullscreen)
{
    unsigned windowFlags = 0;

    if (fullscreen)
        windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

    SDL_Window* window = SDL_CreateWindow(_("Airball"), 0, 0, width, height, windowFlags);

    if (window == nullptr)
    {
        logger_.error(_("SDL window init failed: %s"), SDL_GetError());
        throw VideoError(_("Unable to initialize a window!"));
    }

    return window;
}

SDL_Renderer* Screen::initRenderer()
{
    unsigned rendererFlags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* renderer = SDL_CreateRenderer(window_, -1, rendererFlags);

    if (renderer == nullptr)
    {
        logger_.error(_("SDL renderer init failed: %s"), SDL_GetError());
        throw VideoError(_("Unable to initialize a renderer!"));
    }

    return renderer;
}

Screen::~Screen()
{
    // Destroy from last initialized to the first one
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}

void Screen::update() const
{
    SDL_RenderClear(renderer_);
    SDL_RenderPresent(renderer_);
}


} // namespace airball
