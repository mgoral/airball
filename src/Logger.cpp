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

#include <cstdarg>

#include "Logger.hpp"
#include "Utils.hpp"

namespace airball
{

// initialize static Logger attribute
bool Logger::initialized_ = false;

void Logger::trace(const char* fmt, ...) const
{
#ifndef NDEBUG
    va_list argptr;
    va_start(argptr, fmt);
    SDL_LogVerbose(category_, fmt, argptr);
    va_end(argptr);
#else
    UNUSED_PARAM(fmt);
#endif
}

void Logger::debug(const char* fmt, ...) const
{
#ifndef NDEBUG
    va_list argptr;
    va_start(argptr, fmt);
    SDL_LogDebug(category_, fmt, argptr);
    va_end(argptr);
#else
    UNUSED_PARAM(fmt);
#endif
}

void Logger::info(const char* fmt, ...) const
{
    va_list argptr;
    va_start(argptr, fmt);
    SDL_LogInfo(category_, fmt, argptr);
    va_end(argptr);
}

void Logger::warning(const char* fmt, ...) const
{
    va_list argptr;
    va_start(argptr, fmt);
    SDL_LogWarn(category_, fmt, argptr);
    va_end(argptr);
}

void Logger::error(const char* fmt, ...) const
{
    va_list argptr;
    va_start(argptr, fmt);
    SDL_LogError(category_, fmt, argptr);
    va_end(argptr);
}

void Logger::init()
{
    if (!initialized_)
    {
#ifndef NDEBUG
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#else
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);
#endif
        initialized_ = true;
    }
}

} // namespace airball
