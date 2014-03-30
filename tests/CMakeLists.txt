# tests/CMakeLists.txt

# gmock warning suppressions
add_definitions(-Wno-unused-local-typedefs)
remove_definitions(-pedantic)

set(GMOCK_DIR  ${AIRBALL_LIBS_DIR}/gmock)
set(GTEST_DIR  ${GMOCK_DIR}/gtest)

include_directories(
    ${GMOCK_DIR}/include
    ${GTEST_DIR}/include

    ${AIRBALL_TESTS_DIR}
    ${AIRBALL_SRC_DIR}

    ${Boost_INCLUDE_DIRS}
)

file(GLOB_RECURSE AIRBALL_TESTS_SOURCESS
    ${AIRBALL_SRC_DIR}/map/*.cpp
    ${AIRBALL_SRC_DIR}/states/*.cpp

    # Selective files compiling. Remember to not add main.cpp!
    ${AIRBALL_SRC_DIR}/EventHandler.cpp
    ${AIRBALL_SRC_DIR}/Animation.cpp
    ${AIRBALL_SRC_DIR}/Logger.cpp
    ${AIRBALL_SRC_DIR}/Renderable.cpp
    ${AIRBALL_SRC_DIR}/Resources.cpp
    ${AIRBALL_SRC_DIR}/Screen.cpp

    *.cpp)
set(AIRBALL_TESTS_BIN ${PROJECT_NAME}_ut)

add_executable(${AIRBALL_TESTS_BIN} ${AIRBALL_TESTS_SOURCESS})
target_link_libraries(
    ${AIRBALL_TESTS_BIN}

    # First link test environment
    gmock
    gtest

    # Additional libraries
    ${Boost_LIBRARIES}
)

add_custom_target(
    ${AIRBALL_TESTS_BIN}_run
    COMMAND ${AIRBALL_TESTS_BIN}
    DEPENDS ${AIRBALL_TESTS_BIN}
    WORKING_DIRECTORY ${CMAKE_BUILD_DIR}
    COMMENT "Executing test suite..."
)
