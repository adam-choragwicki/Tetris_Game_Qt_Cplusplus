set(GOOGLETEST_VERSION 1.17.0)

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()

add_subdirectory(googletest)

set(TEST_SOURCES
        src/placed_squares_test.cpp
        src/block_creation_test.cpp
        src/block_movement_test.cpp
        src/block_rotation_test.cpp
        src/block_drop_test.cpp
        src/placed_squares_test.cpp)

add_executable(${PROJECT_NAME}Test_run ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}Test_run PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}Test_run PRIVATE gtest_main ${PROJECT_NAME}Backend)
