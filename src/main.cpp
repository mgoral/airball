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

#include <cstdlib>
#include <stdexcept>
#include <initializer_list>

#include "Logger.hpp"
#include "Translate.hpp"
#include "Application.hpp"

void terminateHandler()
{
    airball::Logger log(airball::LogCategorySystem);
    log.info(_("Terminating"));
    std::_Exit(EXIT_FAILURE);
}

int main()
{
    std::set_terminate(&terminateHandler);

    airball::Logger::init();

    try
    {
        airball::Application app;
        return app.run();
    }
    catch (const std::exception& e)
    {
        airball::Logger log(airball::LogCategoryApplication);
        log.error(_("Critical error occured during program execution:"));
        log.error(e.what());
        std::terminate();
    }

    // Usually program shouldn't go THAT far...
    return 3;
}

