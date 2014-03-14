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
)

file(GLOB_RECURSE AIRBALL_TESTS_SOURCESS 
    ${AIRBALL_SRC_DIR}/objects/*.cpp
    ${AIRBALL_SRC_DIR}/states/*.cpp
    ${AIRBALL_SRC_DIR}/Renderable.cpp
    *.cpp)
set(AIRBALL_TESTS_BIN ${PROJECT_NAME}_ut)

add_executable(${AIRBALL_TESTS_BIN} ${AIRBALL_TESTS_SOURCESS})
target_link_libraries(
    ${AIRBALL_TESTS_BIN}

    # First link test environment
    gmock
    gtest
)

add_custom_target(
    ${AIRBALL_TESTS_BIN}_run
    COMMAND ${AIRBALL_TESTS_BIN}
    DEPENDS ${AIRBALL_TESTS_BIN}
    WORKING_DIRECTORY ${CMAKE_BUILD_DIR}
    COMMENT "Executing test suite..."
)
