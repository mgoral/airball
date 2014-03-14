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

#include <algorithm>
#include <functional>

#include "StateStack.hpp"

namespace airball
{
namespace states
{

StateStack::StateStack()
{
}

StateStack::~StateStack()
{
    while (stateStack_.size() > 0)
    {
        stateStack_.pop_back();
    }
}

void StateStack::update()
{
    // Just in case e.g. state calls update as a callback
    if (updateStarted_.locked())
        return;

    LockGuard<ScopeLock> lock(updateStarted_);

    // First process events from previous updates
    processEvents();

    if (!empty())
    {
        std::unique_ptr<IState>& currentState = stateStack_.back();
        currentState->update(*this);
    }
}

void StateStack::handleEvent(SDL_Event& event)
{
    if (updateStarted_.locked())
        return;

    if (!empty())
    {
        std::unique_ptr<IState>& currentState = stateStack_.back();
        currentState->handleEvent(event);
    }
}

void StateStack::draw(Screen& screen)
{
    if (updateStarted_.locked())
        return;

    if (!empty())
    {
        std::unique_ptr<IState>& currentState = stateStack_.back();
        currentState->draw(screen);
    }
}

void StateStack::push(std::unique_ptr<IState> state)
{
    if (state)
    {
        // I didn't manage to make std::bind work with unique_ptr. Lambda that captures references
        // ([&]()) also doesn't work because the reference will be null. So we have to manually
        // repack this pointer to the new unique_ptr which is then normally passed to pushEvent.
        IState* rawState = state.release();
        std::function<void()> event = [=]() {
            std::unique_ptr<IState> newState(rawState);
            pushEvent(std::move(newState));
        };
        events_.push_back(event);
    }
}

void StateStack::pushEvent(std::unique_ptr<IState> state)
{
    if (stateStack_.size() > 0)
    {
        std::unique_ptr<IState>& currentState = stateStack_.back();
        currentState->onOverride();
    }

    state->onEnter();
    stateStack_.push_back(std::move(state));
}

void StateStack::pop()
{
    std::function<void()> event = std::bind(&StateStack::popEvent, this);
    events_.push_back(event);
}


void StateStack::popEvent()
{
    if (stateStack_.size() > 0)
    {
        std::unique_ptr<IState>& currentState = stateStack_.back();
        currentState->onExit();
        stateStack_.pop_back();
    }
}

void StateStack::processEvents()
{
    for (auto event : events_)
        event();
    events_.clear();
}

bool StateStack::empty() const
{
    return stateStack_.empty();
}

unsigned StateStack::size() const
{
    return stateStack_.size();
}

} // namespace states
} // namespace airball
