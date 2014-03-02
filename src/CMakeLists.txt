# src/CMakeLists.txt

add_definitions(-Werror)

# General includes
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}

    # Headers for used libraries
    ${GETTEXT_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

# libobjects
file(GLOB_RECURSE LIB_OBJECTS_SOURCES objects/*.cpp)
add_library(objects STATIC ${LIB_OBJECTS_SOURCES})

# libstates
file(GLOB_RECURSE LIB_STATES_SOURCES states/*.cpp)
add_library(states STATIC ${LIB_STATES_SOURCES})


# main executable
file(GLOB AIRBALL_SOURCES *.cpp)
set(AIRBALL_BIN ${PROJECT_NAME})

add_executable(${AIRBALL_BIN} ${AIRBALL_SOURCES})
target_link_libraries(
    ${AIRBALL_BIN}

    # Helper libs
    objects
    states

    # used libraries
    ${GETTEXT_LIBRARIES}
    ${SDL2_LIBRARIES}
)

