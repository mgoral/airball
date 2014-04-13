# src/CMakeLists.txt

add_definitions(-Werror)

# General includes
include_directories(
    ${AIRBALL_SRC_DIR}

    # Headers for used libraries
    ${GETTEXT_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR}
)

# main executable
file(GLOB AIRBALL_SOURCES
    components/*.cpp
    map/*.cpp
    map/detail/*.cpp
    states/*.cpp
    *.cpp)
set(AIRBALL_BIN ${PROJECT_NAME})

add_executable(${AIRBALL_BIN} ${AIRBALL_SOURCES})
target_link_libraries(
    ${AIRBALL_BIN}

    # used libraries
    ${GETTEXT_LIBRARIES}
    ${Boost_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)

