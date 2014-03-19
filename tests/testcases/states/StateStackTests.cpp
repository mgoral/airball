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

#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mocks/IStateMock.hpp"
#include "states/StateStack.hpp"

using testing::_;

typedef std::unique_ptr<airball::mocks::IStateMock> UniqueStateMock;

class StateStackTests : public ::testing::Test
{
public:
    StateStackTests() :
        mockProxy_(new airball::mocks::IStateMockProxy(stateMock_)),
        mockProxy2_(new airball::mocks::IStateMockProxy(stateMock2_))
    {
    }

protected:
    // To get around limitations regarding usage of unique_ptr, we'll declare a proxy class that
    // simply forwards all calls to IStateMock stored inside it.
    airball::mocks::IStateMock stateMock_;
    airball::mocks::IStateMock stateMock2_;
    std::unique_ptr<airball::mocks::IStateMockProxy> mockProxy_;
    std::unique_ptr<airball::mocks::IStateMockProxy> mockProxy2_;
    airball::states::StateStack stateStack_;
};

TEST_F(StateStackTests, StateStackShouldCallStateOnEnterAfterUpdate)
{
    stateStack_.push(std::move(mockProxy_));
    EXPECT_CALL(stateMock_, onEnter()).Times(1);
    EXPECT_CALL(stateMock_, update(testing::Ref(stateStack_))).Times(1);
    stateStack_.update();
}

TEST_F(StateStackTests, StateStackShouldCallOnOverrideBeforePushingANewState)
{
    stateStack_.push(std::move(mockProxy_));
    EXPECT_CALL(stateMock_, onEnter()).Times(1);
    EXPECT_CALL(stateMock_, update(testing::Ref(stateStack_))).Times(1);
    stateStack_.update();

    stateStack_.push(std::move(mockProxy2_));
    testing::InSequence seq;
    EXPECT_CALL(stateMock_, onOverride()).Times(1);
    EXPECT_CALL(stateMock2_, onEnter()).Times(1);
    EXPECT_CALL(stateMock2_, update(testing::Ref(stateStack_))).Times(1);
    stateStack_.update();
}

TEST_F(StateStackTests, SingleUpdateUpdatesOnlyTopState)
{
    stateStack_.push(std::move(mockProxy_));
    EXPECT_CALL(stateMock_, onEnter()).Times(1);
    EXPECT_CALL(stateMock_, update(_)).Times(0);

    stateStack_.push(std::move(mockProxy2_));
    EXPECT_CALL(stateMock_, onOverride()).Times(1);
    EXPECT_CALL(stateMock2_, onEnter()).Times(1);
    EXPECT_CALL(stateMock2_, update(testing::Ref(stateStack_))).Times(1);

    stateStack_.update();
}

TEST_F(StateStackTests, OnlyTopStateIsPopped)
{
    stateStack_.push(std::move(mockProxy_));
    EXPECT_CALL(stateMock_, onEnter()).Times(1); 
    stateStack_.push(std::move(mockProxy2_));
    EXPECT_CALL(stateMock_, onOverride()).Times(1);
    EXPECT_CALL(stateMock2_, onEnter()).Times(1);
    EXPECT_CALL(stateMock2_, update(testing::Ref(stateStack_))).Times(1);

    stateStack_.update();

    EXPECT_CALL(stateMock2_, onExit()).Times(1);
    stateStack_.pop();

    EXPECT_CALL(stateMock_, update(_)).Times(1);
    stateStack_.update();

}
