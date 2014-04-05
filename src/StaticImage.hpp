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

#ifndef AIRBALL_STATICIMAGE_HPP_
#define AIRBALL_STATICIMAGE_HPP_

#include <string>

#include "Renderable.hpp"

namespace airball
{

class StaticImage : public Renderable
{
public:
    explicit StaticImage(const std::string& imageName) : imageName_(imageName)
    {
    }

    std::string imageName() const
    {
        return imageName_;
    }

private:
    std::string imageName_;
};

} // namespace airball

#endif // AIRBALL_STATICIMAGE_HPP_
