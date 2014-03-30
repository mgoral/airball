# CMakeLists.txt

cmake_minimum_required(VERSION 2.6)

if (NOT DEFINED AIRBALL_PROJECT_NAME)
    set(AIRBALL_PROJECT_NAME airball)
endif()
project(${AIRBALL_PROJECT_NAME})

# Add CMake modules from "cmake" directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

# Set the output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")

# Allow usage of pkg-config
include(FindPkgConfig)

# Required packages
find_package(Gettext REQUIRED)
find_package(Boost 1.41.0 REQUIRED)
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

# Configure airball installation paths. These are usually passed via a Makefile, but we'll check
# them just in case and set to default values if they were not passed.
# We do it before adding subdirectories so child CMakeLists can use them.
if (NOT DEFINED AIRBALL_INSTALL_DIR)
    set(AIRBALL_INSTALL_DIR share/airball)
endif()
if (NOT DEFINED AIRBALL_EXECUTABLE_DIR)
    set(AIRBALL_EXECUTABLE_DIR bin)
endif()

add_subdirectory(src)
add_subdirectory(tests EXCLUDE_FROM_ALL)
add_subdirectory(thirdparty)

configure_file(airball.in ${CMAKE_INSTALL_PREFIX}/${AIRBALL_BIN_DIR}/${PROJECT_NAME} @ONLY)
install(DIRECTORY resources DESTINATION ${AIRBALL_INSTALL_DIR})
# Hack. We can only hope that there is bin/${PROJECT_NAME} created
install(PROGRAMS bin/${PROJECT_NAME} DESTINATION ${AIRBALL_INSTALL_DIR})

# Uninstall target
# See: http://www.cmake.org/Wiki/CMake_FAQ#Can_I_do_.22make_uninstall.22_with_CMake.3F
configure_file(
    "${CMAKE_MODULE_PATH}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
