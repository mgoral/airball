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

#ifndef AIRBALL_MOCKS_SDLMOCK_HPP_
#define AIRBALL_MOCKS_SDLMOCK_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <gmock/gmock.h>

// No namespace on purpose

class SDLMock
{
    SDLMock();

    MOCK_METHOD4(SDL_LogMessageV, void(int, SDL_LogPriority, const char*, va_list));
    MOCK_METHOD1(SDL_LogSetAllPriority, void(SDL_LogPriority));

    MOCK_METHOD2(SDL_CreateTextureFromSurface, SDL_Texture*(SDL_Renderer*, SDL_Surface*));
    MOCK_METHOD1(SDL_FreeSurface, void(SDL_Surface*));
    MOCK_METHOD1(SDL_DestroyTexture, void(SDL_Texture*));

    MOCK_METHOD6(SDL_CreateWindow, SDL_Window*(const char*, int, int, int, int, Uint32));
    MOCK_METHOD1(SDL_DestroyWindow, void(SDL_Window*));

    MOCK_METHOD0(SDL_GetError, const char*());

    MOCK_METHOD3(SDL_CreateRenderer, SDL_Renderer*(SDL_Window*, int, Uint32));
    MOCK_METHOD1(SDL_DestroyRenderer, void(SDL_Renderer*));
    MOCK_METHOD1(SDL_RenderPresent, void(SDL_Renderer*));
    MOCK_METHOD4(SDL_RenderCopy,
        int(SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const SDL_Rect*));
    MOCK_METHOD1(SDL_RenderClear, int(SDL_Renderer*));

    MOCK_METHOD1(IMG_Load, SDL_Surface*(const char*));
};


#endif // AIRBALL_MOCKS_SDLMOCK_HPP_
