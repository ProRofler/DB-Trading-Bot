cmake_minimum_required(VERSION 3.10)

# Collect all test sources
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

if(TEST_SOURCES)
    message(STATUS "Found test sources: ${TEST_SOURCES}")

    # Collect project sources to link with tests
    file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
    list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")
    
    if(PROJECT_SOURCES)
        message(STATUS "Found project sources for tests: ${PROJECT_SOURCES}")
    else()
        message(FATAL_ERROR "No project sources found in ${CMAKE_SOURCE_DIR}/src")
    endif()

    # Create test executable including both project sources and test sources
    add_executable(DB_Trading_Bot_Tests ${PROJECT_SOURCES} ${TEST_SOURCES})

    # Include project headers
    target_include_directories(DB_Trading_Bot_Tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

    # Link Google Test
    target_link_libraries(DB_Trading_Bot_Tests PRIVATE gtest gtest_main)

    find_package(CURL REQUIRED)
    target_link_libraries(DB_Trading_Bot_Tests PRIVATE CURL::libcurl)

    set_target_properties(DB_Trading_Bot_Tests PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )


    # Register with CTest
    enable_testing()
    add_test(NAME DB_Trading_Bot_Tests COMMAND DB_Trading_Bot_Tests)
else()
    message(WARNING "No test sources found in ${CMAKE_CURRENT_SOURCE_DIR}")
endif()
