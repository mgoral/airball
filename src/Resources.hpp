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

#ifndef AIRBALL_RESOURCES_HPP_
#define AIRBALL_RESOURCES_HPP_

#include <stdexcept>
#include <mutex>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <boost/filesystem.hpp>

#include <SDL2/SDL.h>

namespace boostfs = boost::filesystem;

namespace airball
{

#ifdef WIN32
    const static std::string PATH_SEP = "\\";
#else
    const static std::string PATH_SEP = "/";
#endif

class ResourcesError : public std::runtime_error
{
public:
    explicit ResourcesError(const std::string& what) : std::runtime_error(what)
    {
    }

    explicit ResourcesError(const char* what) : std::runtime_error(what)
    {
    }
};

class Resources
{
public:
    using FileName = std::string;

    template<typename T>
    using ResourceList = std::unordered_map<FileName, T>;

    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    static SDL_Texture* getImage(const FileName& imageName, SDL_Renderer* renderer);
    static void releaseImage(const FileName& imageName);

protected:
    static std::string getResourcesRootDir();
    static std::string joinPath(std::initializer_list<std::string> parts);
    static std::string getFilePath(const FileName& partialPath);

    static void loadImage(const ResourceList<SDL_Texture*>::iterator& imageIt, SDL_Renderer* renderer);

private:
    static ResourceList<SDL_Texture*> images_;
    const static boostfs::path airballDir_;

    // TODO: thread model is not yet created but it's possible that images_ will be used from
    // many threads
    static std::mutex imagesMutex_;
};

} // namespace airball

#endif // AIRBALL_RESOURCES_HPP_
