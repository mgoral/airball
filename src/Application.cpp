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

    const unsigned fpsCap = 50; // TODO: read from config file
    const unsigned maxFrameSkip = 10;

    std::chrono::nanoseconds timePerUpdate(1000000000 / fpsCap);
    std::chrono::nanoseconds lag(0);
    auto previousTime = std::chrono::system_clock::now();

    bool saveCpu = true; // TODO: read from config file
    unsigned loopCount = 0;

    // We will render as fast as possible, but the game will be updated only 'fpsCap' times per
    // second. We can also sleep (if we have time for that) to reduce CPU usage.
    while (!stopApp_)
    {
        auto currentTime = std::chrono::system_clock::now();
        auto elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        lag += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsedTime);

        loopCount = 0;
        while (lag >= timePerUpdate && loopCount < maxFrameSkip)
        {
            handleInput(stateStack);
            stateStack.update();
            lag -= timePerUpdate;
            ++loopCount;
        }

        // TODO: add interpolation -- screen.setInterpolation(interpolation); (useful during
        // animations.
        // If object has set Animation (new class consisting vector of Frames), then Screen should
        // display instead its Animation
        // http://www.koonsolo.com/news/dewitters-gameloop/

        stateStack.draw(screen);

        // Sleep for a certain amount of time in case we want to save CPU usage.
        // Note that in fact it takes into consideration previous frame, not the current one.
        if (saveCpu && elapsedTime < timePerUpdate)
        {
            std::this_thread::sleep_for(timePerUpdate - elapsedTime);
        }
    }

    return 0; // end of program, in fact
}

void Application::handleInput(airball::states::StateStack& stateStack)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
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

