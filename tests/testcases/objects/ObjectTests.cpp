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

#include <gtest/gtest.h>

#include "objects/Coordinates.hpp"
#include "objects/Object.hpp"

class ObjectTests : public ::testing::Test
{
public:
    ObjectTests() : radius_(2), zeroRadius_(0)
    {
    }

protected:
    unsigned radius_;
    unsigned zeroRadius_;
};

/**
 * Remember: Airball coordinates in fact start at point (0, 0) located in upper left corner and
 * increment to the left and right. Like this:
 *
 *      (0,0)  (1,0)       [x]
 *        +------|------|--->
 *        |
 *        |
 * (0,1)  -
 *        |
 *        |
 *        -      . (1,2)
 *        |
 *    [y] V
 *
 *  We keep this notation in tests.
 */

TEST_F(ObjectTests, objectsCollideWhenTheyHaveTheSameCoordinates)
{
    airball::objects::Coordinates coord(3, 4);
    airball::objects::Object objRef(coord, radius_);
    airball::objects::Object obj2(coord, zeroRadius_);

    ASSERT_TRUE(objRef.collides(obj2));
}

TEST_F(ObjectTests, objectsOnLeftCollideOnABorder)
{
    airball::objects::Coordinates coord1(0, 0);
    airball::objects::Coordinates coord2(-4, 0);

    airball::objects::Object objRef(coord1, radius_);
    airball::objects::Object obj2(coord2, radius_);

    ASSERT_TRUE(objRef.collides(obj2));
}

TEST_F(ObjectTests, objectsOnLeftDoNotCollide)
{
    airball::objects::Coordinates coord1(0, 0);
    airball::objects::Coordinates coord2(-5, 0);

    airball::objects::Object objRef(coord1, radius_);
    airball::objects::Object obj2(coord2, radius_);

    ASSERT_FALSE(objRef.collides(obj2));
}

TEST_F(ObjectTests, objectsOnRightCollideOnABorder)
{
    airball::objects::Coordinates coord1(0, 0);
    airball::objects::Coordinates coord2(4, 0);

    airball::objects::Object objRef(coord1, radius_);
    airball::objects::Object obj2(coord2, radius_);

    ASSERT_TRUE(objRef.collides(obj2));
}

TEST_F(ObjectTests, objectsOnRightDoNotCollide)
{
    airball::objects::Coordinates coord1(0, 0);
    airball::objects::Coordinates coord2(5, 0);

    airball::objects::Object objRef(coord1, radius_);
    airball::objects::Object obj2(coord2, radius_);

    ASSERT_FALSE(objRef.collides(obj2));
}

TEST_F(ObjectTests, objectsOnTopCollideOnABorder)
{
    airball::objects::Coordinates coord1(0, 0);
    airball::objects::Coordinates coord2(0, -4);

    airball::objects::Object objRef(coord1, radius_);
    airball::objects::Object obj2(coord2, radius_);

    ASSERT_TRUE(objRef.collides(obj2));
}

TEST_F(ObjectTests, objectsOnTopDoNotCollide)
{
    airball::objects::Coordinates coord1(0, 0);
    airball::objects::Coordinates coord2(0, -5);

    airball::objects::Object objRef(coord1, radius_);
    airball::objects::Object obj2(coord2, radius_);

    ASSERT_FALSE(objRef.collides(obj2));
}

TEST_F(ObjectTests, objectsOnBottomCollideOnABorder)
{
    airball::objects::Coordinates coord1(0, 0);
    airball::objects::Coordinates coord2(0, 4);

    airball::objects::Object objRef(coord1, radius_);
    airball::objects::Object obj2(coord2, radius_);

    ASSERT_TRUE(objRef.collides(obj2));
}

TEST_F(ObjectTests, objectsOnBottomDoNotCollide)
{
    airball::objects::Coordinates coord1(0, 0);
    airball::objects::Coordinates coord2(0, 5);

    airball::objects::Object objRef(coord1, radius_);
    airball::objects::Object obj2(coord2, radius_);

    ASSERT_FALSE(objRef.collides(obj2));
}
