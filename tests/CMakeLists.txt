# tests/CMakeLists.txt

add_definitions(-O0 -fno-inline)

set(GMOCK_DIR  ${AIRBALL_LIBS_DIR}/gmock)
set(GTEST_DIR  ${GMOCK_DIR}/gtest)

include_directories(
    ${GMOCK_DIR}/include
    ${GTEST_DIR}/include

    ${AIRBALL_SRC_DIR}
    ${AIRBALL_SRC_DIR}/objects
)

file(GLOB AIRBALL_TESTS_SOURCESS ./*.cpp)
set(AIRBALL_TESTS_BIN ${PROJECT_NAME}_ut)

add_executable(${AIRBALL_TESTS_BIN} ${AIRBALL_TESTS_SOURCESS})
target_link_libraries(
    ${AIRBALL_TESTS_BIN}

    # First link test environment
    gmock
    gtest

    # Then link helper libs
    objects
)

add_custom_target(
    ${AIRBALL_TESTS_BIN}_run
    COMMAND ${AIRBALL_TESTS_BIN}
    DEPENDS ${AIRBALL_TESTS_BIN}
    WORKING_DIRECTORY ${CMAKE_BUILD_DIR}
    COMMENT "Executing test suite..."
)
