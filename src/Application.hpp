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

#ifndef AIRBALL_APPLICATION_HPP_
#define AIRBALL_APPLICATION_HPP_

#include <stdexcept>
#include <string>

#include "Logger.hpp"
#include "Screen.hpp"

#include "states/StateStack.hpp"

namespace airball
{

class ApplicationError : public std::runtime_error
{
public:
    explicit ApplicationError(const std::string& what) : std::runtime_error(what)
    {
    }

    explicit ApplicationError(const char* what) : std::runtime_error(what)
    {
    }
};

class Application
{
public:
    Application();
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    int run();

private:
    void handleInput(airball::states::StateStack& stateStack);

private:
    airball::Logger logger_;
    bool stopApp_;
};

} // namespace airball

#endif // AIRBALL_APPLICATION_HPP_
