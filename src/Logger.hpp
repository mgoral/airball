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

#ifndef AIRBALL_LOGGER_HPP_
#define AIRBALL_LOGGER_HPP_

#include <SDL2/SDL.h>

namespace airball
{

enum LogCategory
{
    LogCategoryApplication = SDL_LOG_CATEGORY_APPLICATION,
    LogCategoryError = SDL_LOG_CATEGORY_ERROR,
    LogCategorySystem = SDL_LOG_CATEGORY_SYSTEM,
    LogCategoryAudio = SDL_LOG_CATEGORY_AUDIO,
    LogCategoryVideo = SDL_LOG_CATEGORY_VIDEO,
    LogCategoryRender = SDL_LOG_CATEGORY_RENDER,
    LogCategoryInput = SDL_LOG_CATEGORY_INPUT,

    // Custom categories
    LogCategoryState = SDL_LOG_CATEGORY_CUSTOM,
    LogCategoryMap
};

class Logger
{
public:
    explicit Logger(LogCategory category);

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Print all kinds of logs with different priorities
    void trace(const char* fmt, ...) const;
    void debug(const char* fmt, ...) const;
    void info(const char* fmt, ...) const;
    void warning(const char* fmt, ...) const;
    void error(const char* fmt, ...) const;

private:
    // Initialize default logs priority.
    static void init();

private:
    int category_;
    static bool initialized_;
};

} // namespace airball

#endif // AIRBALL_LOGGER_HPP_
