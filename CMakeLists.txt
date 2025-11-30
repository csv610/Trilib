cmake_minimum_required(VERSION 3.10)
project(Trilib)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Add the library (header-only)
add_library(trilib INTERFACE)
target_include_directories(trilib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Option to build tests
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    # Enable testing
    enable_testing()

    # Find Google Test
    find_package(GTest QUIET)

    if(NOT GTest_FOUND)
        # Download and build Google Test
        include(FetchContent)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
            QUIET
        )

        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()

    # Create test executable for trilib
    add_executable(test_trilib test/test_trilib.cpp)
    target_link_libraries(test_trilib
        PRIVATE
        trilib
        GTest::gtest
        GTest::gtest_main
    )
    add_test(NAME TriLibTests COMMAND test_trilib)

    # Create test executable for veclib
    add_executable(test_veclib test/test_veclib.cpp)
    target_link_libraries(test_veclib
        PRIVATE
        trilib
        GTest::gtest
        GTest::gtest_main
    )
    add_test(NAME VecLibTests COMMAND test_veclib)
endif()

# Build example executable
option(BUILD_EXAMPLES "Build examples" ON)

if(BUILD_EXAMPLES)
    add_executable(example example.cpp)
    target_link_libraries(example PRIVATE trilib)
endif()
