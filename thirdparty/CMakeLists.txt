# thirdparty/CMakeLists.txt

# gmock warning suppressions
add_definitions(-Wno-unused-local-typedefs)
remove_definitions(-pedantic)

add_subdirectory(gmock EXCLUDE_FROM_ALL)

remove_definitions(-Wno-unused-local-typedefs)
