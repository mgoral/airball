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

#include <thread>
#include <chrono>
#include <memory>

#include <SDL2/SDL.h>

#include "Application.hpp"

#include "states/GameState.hpp"

#include "detail/Translate.hpp"

namespace airball
{

Application::Application() : logger_(airball::LogCategoryApplication), stopApp_(false)
{
    const unsigned subsystemsToInit =
        SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS;

    if (0 != SDL_Init(subsystemsToInit))
    {
        throw ApplicationError(_("Could not initialize SDL!"));
    }
}

Application::~Application()
{
    logger_.debug(_("Performing a clean application exit."));
    SDL_Quit();
}

int Application::run()
{
    logger_.debug(_("Running Airball"));

    airball::Screen screen(100, 100);

    states::StateStack stateStack;
    std::unique_ptr<states::IState> initialState(new states::GameState());
    stateStack.push(std::move(initialState));

    while (!stopApp_)
    {
        handleInput(stateStack);
        stateStack.update();
        stateStack.draw(screen);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));  // FIXME: temporary solution
    }

    return 0;
}

void Application::handleInput(airball::states::StateStack& stateStack)
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                stopApp_ = true;
                // TODO: clear stateStack
                // maybe add it after main loop (i.e. when while (!stopApp_) finishes, call OnExit
                // on all states and pop them
                break;
            default:
                stateStack.handleEvent(event);
        }
    }
}

} // namespace airball

