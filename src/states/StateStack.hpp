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

#ifndef AIRBALL_STATES_STATESTACK_HPP_
#define AIRBALL_STATES_STATESTACK_HPP_

#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "IState.hpp"
#include "Screen.hpp"
#include "Logger.hpp"

namespace airball
{
namespace states
{

/**
 * ScopeLock is used to check if state doesn't call certain methods as a callback (it may try to
 * incorrectly do this e.g. during update()).
 *
 * Don't use lock() and unlock() directly. Use a LockGuard, a nice RAII wrapper.
 */
class ScopeLock
{
public:
    ScopeLock() : locked_(false) { }

    void lock()
    {
        locked_ = true;
    }

    void unlock()
    {
        locked_ = false;
    }

    bool locked() const
    {
        return locked_;
    }

private:
    bool locked_;
};

template <class Lock>
class LockGuard
{
public:
    explicit LockGuard(Lock& lock) : lock_(lock)
    {
        lock_.lock();
    }

    ~LockGuard()
    {
        lock_.unlock();
    }

    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;

private:
    Lock& lock_;
};

class StateStack
{
public:
    StateStack();
    ~StateStack();

    void push(std::unique_ptr<IState> state);
    void pop();

    bool empty() const;
    unsigned size() const;

    void update();
    void handleEvent(SDL_Event& event);
    void draw(Screen& screen);


private:
    void processEvents();

    void pushEvent(std::unique_ptr<IState> state);
    void popEvent();

private:
    std::vector<std::unique_ptr<IState>> stateStack_;
    std::vector<std::function<void()>> events_;
    ScopeLock updateStarted_;
};

} // namespace states
} // namespace airball

#endif // AIRBALL_STATES_STATESTACK_HPP_
