cmake_minimum_required(VERSION 3.10)

# Tests CMake for DB_Trading_Bot

file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

if(TEST_SOURCES)
    add_executable(tests_sample ${TEST_SOURCES})

    target_include_directories(tests_sample PRIVATE ${CMAKE_SOURCE_DIR}/include)

    target_link_libraries(tests_sample PRIVATE gtest gtest_main)

    add_test(NAME DB_Trading_Bot_Tests COMMAND tests_sample)
else()
    message(WARNING "No test sources found in ${CMAKE_CURRENT_SOURCE_DIR}")
endif()