# CMakeLists.txt

cmake_minimum_required(VERSION 2.6)
project(airball)

# Global definitions appliable for all targets
add_definitions(-Wall -Wextra -pedantic -std=c++11)

set(AIRBALL_SRC_DIR    ${PROJECT_SOURCE_DIR}/src)
set(AIRBALL_TESTS_DIR  ${PROJECT_SOURCE_DIR}/tests)
set(AIRBALL_LIBS_DIR   ${PROJECT_SOURCE_DIR}/thirdparty)

add_subdirectory(src)
add_subdirectory(tests EXCLUDE_FROM_ALL)
add_subdirectory(thirdparty)
