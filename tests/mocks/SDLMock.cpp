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
 * along with This program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <functional>

#include "SDLMock.hpp"

static std::function<void(int, SDL_LogPriority, const char*, va_list)> SDL_LogMessageVCallback;
static std::function<void(SDL_LogPriority)> SDL_LogSetAllPriorityCallback;

static std::function<SDL_Texture*(SDL_Renderer*, SDL_Surface*)>
    SDL_CreateTextureFromSurfaceCallback;
static std::function<void(SDL_Surface*)> SDL_FreeSurfaceCallback;
static std::function<void(SDL_Texture*)> SDL_DestroyTextureCallback;

static std::function<SDL_Window*(const char*, int, int, int, int, Uint32)> SDL_CreateWindowCallback;
static std::function<void(SDL_Window*)> SDL_DestroyWindowCallback;

static std::function<const char*()> SDL_GetErrorCallback;

static std::function<SDL_Renderer*(SDL_Window*, int, Uint32)> SDL_CreateRendererCallback;
static std::function<void(SDL_Renderer*)> SDL_DestroyRendererCallback;
static std::function<void(SDL_Renderer*)> SDL_RenderPresentCallback;
static std::function<int(SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const SDL_Rect*)>
    SDL_RenderCopyCallback;
static std::function<int(SDL_Renderer*)> SDL_RenderClearCallback;

static std::function<SDL_Surface*(const char*)> IMG_LoadCallback;

SDLMock::SDLMock()
{
    using namespace std::placeholders;

    SDL_LogMessageVCallback = std::bind(&SDLMock::SDL_LogMessageV, this, _1, _2, _3, _4);
    SDL_LogSetAllPriorityCallback = std::bind(&SDLMock::SDL_LogSetAllPriority, this, _1);

    SDL_CreateTextureFromSurfaceCallback = std::bind(
        &SDLMock::SDL_CreateTextureFromSurface, this, _1, _2);
    SDL_FreeSurfaceCallback = std::bind(&SDLMock::SDL_FreeSurface, this, _1);
    SDL_DestroyTextureCallback = std::bind(&SDLMock::SDL_DestroyTexture, this, _1);

    SDL_CreateWindowCallback = std::bind(&SDLMock::SDL_CreateWindow, this, _1, _2, _3, _4, _5, _6);
    SDL_DestroyWindowCallback = std::bind(&SDLMock::SDL_DestroyWindow, this, _1);

    SDL_GetErrorCallback = std::bind(&SDLMock::SDL_GetError, this);

    SDL_CreateRendererCallback = std::bind(&SDLMock::SDL_CreateRenderer, this, _1, _2, _3);
    SDL_DestroyRendererCallback = std::bind(&SDLMock::SDL_DestroyRenderer, this, _1);
    SDL_RenderPresentCallback = std::bind(&SDLMock::SDL_RenderPresent, this, _1);
    SDL_RenderCopyCallback = std::bind(&SDLMock::SDL_RenderCopy, this, _1, _2, _3, _4);
    SDL_RenderClearCallback = std::bind(&SDLMock::SDL_RenderClear, this, _1);

    IMG_LoadCallback = std::bind(&SDLMock::IMG_Load, this, _1);
}

extern "C"
{

void SDL_LogMessageV(int category, SDL_LogPriority priority, const char* fmt, va_list ap)
{
    SDL_LogMessageVCallback(category, priority, fmt, ap);
}

SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface*  surface)
{
    return SDL_CreateTextureFromSurfaceCallback(renderer, surface);
}


void SDL_LogSetAllPriority(SDL_LogPriority priority)
{
    SDL_LogSetAllPriorityCallback(priority);
}

void SDL_FreeSurface(SDL_Surface* surface)
{
    SDL_FreeSurfaceCallback(surface);
}

void SDL_DestroyTexture(SDL_Texture* texture)
{
    SDL_DestroyTextureCallback(texture);
}

SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags)
{
    return SDL_CreateWindowCallback(title, x, y, w, h, flags);
}

void SDL_DestroyWindow(SDL_Window* window)
{
    SDL_DestroyWindowCallback(window);
}

const char* SDL_GetError(void)
{
    return SDL_GetErrorCallback();
}

SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags)
{
    return SDL_CreateRendererCallback(window, index, flags);
}

void SDL_DestroyRenderer(SDL_Renderer* renderer)
{
    return SDL_DestroyRendererCallback(renderer);
}

void SDL_RenderPresent(SDL_Renderer* renderer)
{
    SDL_RenderPresentCallback(renderer);
}

int SDL_RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcrect,
    const SDL_Rect* dstrect)
{
    return SDL_RenderCopyCallback(renderer, texture, srcrect, dstrect);
}

int SDL_RenderClear(SDL_Renderer* renderer)
{
    return SDL_RenderClearCallback(renderer);
}


SDL_Surface *IMG_Load(const char *file)
{
    return IMG_LoadCallback(file);
}

} // extern "C"
