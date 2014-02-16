# src/CMakeLists.txt

add_definitions(-Werror)

# General includes
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    game
)

# libgame
file(GLOB_RECURSE LIB_GAME_SOURCES game/*.cpp)
add_library(game STATIC ${LIB_GAME_SOURCES})


# main executable
set(AIRBALL_SOURCES main.cpp)
set(AIRBALL_BIN ${PROJECT_NAME})

add_executable(${AIRBALL_BIN} ${AIRBALL_SOURCES})
target_link_libraries(
    ${AIRBALL_BIN}

    # Helper libs
    game
)

