/**
 * Copyright (C) Michal Goral, 2014
 *
 * Airball is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Airball is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Airball; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef AIRBALL_MOCKS_ISTATEMOCK_HPP_
#define AIRBALL_MOCKS_ISTATEMOCK_HPP_

#include <gmock/gmock.h>

#include "states/IState.hpp"

namespace airball
{
namespace mocks
{

class IStateMock : public airball::states::IState
{
public:
    MOCK_METHOD0(onEnter, void());
    MOCK_METHOD0(onExit, void());
    MOCK_METHOD0(onOverride, void());
    MOCK_METHOD0(onResume, void());
    MOCK_METHOD1(handleEvent, void(SDL_Event&));
    MOCK_METHOD1(update, void(airball::states::StateStack&));
    MOCK_METHOD1(draw, void(airball::Screen&));
};

class IStateMockProxy : public airball::states::IState
{
public:
    explicit IStateMockProxy(IStateMock& stateMock) : storedMock(stateMock)
    {
    }

    void onEnter()
    {
        storedMock.onEnter();
    }

    void onExit()
    {
        storedMock.onExit();
    }

    void onOverride()
    {
        storedMock.onOverride();
    }

    void handleEvent(SDL_Event& event)
    {
        storedMock.handleEvent(event);
    }

    void onResume()
    {
        storedMock.onResume();
    }

    void update(airball::states::StateStack& stack)
    {
        storedMock.update(stack);
    }

    void draw(airball::Screen& screen)
    {
        storedMock.draw(screen);
    }

private:
    IStateMock& storedMock;
};

} // namespace mocks
} // namespace airball

#endif // AIRBALL_MOCKS_ISTATEMOCK_HPP_
