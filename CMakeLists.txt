# CMakeLists.txt

cmake_minimum_required(VERSION 2.6)
project(airball)

# Add CMake modules from "cmake" directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

# Set the output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")

# Allow usage of pkg-config
include(FindPkgConfig)

# Required packages
find_package(Gettext REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)

# Global definitions appliable for all targets
add_definitions(-Wall -Wextra -pedantic -std=c++11)

# OS specific global flags
if(WIN32)
    add_definitions(-DWIN32)
elseif(UNIX)
    add_definitions(-DUNIX)
endif()

# Additional flags passed by user
add_definitions(${ADDITIONAL_CXX_FLAGS})

set(AIRBALL_SRC_DIR    ${PROJECT_SOURCE_DIR}/src)
set(AIRBALL_TESTS_DIR  ${PROJECT_SOURCE_DIR}/tests)
set(AIRBALL_LIBS_DIR   ${PROJECT_SOURCE_DIR}/thirdparty)

add_subdirectory(src)
add_subdirectory(tests EXCLUDE_FROM_ALL)
add_subdirectory(thirdparty)
