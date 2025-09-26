    cmake_minimum_required(VERSION 3.22)

    set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
    set(PROJECT_VERSION 0.0.${PATCH_VERSION})

    project(DB_Trading_Bot VERSION ${PROJECT_VERSION})

    if(MINGW)
        link_libraries(ws2_32 wsock32)
    endif()

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    # Collect headers and sources from conventional folders
    file(GLOB_RECURSE SAMPLE_HEADERS ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/include/*.hpp)
    file(GLOB_RECURSE SAMPLE_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.cc ${CMAKE_SOURCE_DIR}/src/*.cxx)

    if(SAMPLE_SOURCES)
        add_executable(${PROJECT_NAME} ${SAMPLE_SOURCES} ${SAMPLE_HEADERS})
    else()
        message(FATAL_ERROR "No source files (*.cpp, *.cc, *.cxx) found in 'src/' — ensure your sources are placed under src/ or update CMakeLists.txt.")
    endif()

    # Ensure the project's include directory is visible to the target
    target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

    set(CPACK_PROJECT_NAME ${PROJECT_NAME})
    set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
    include(CPack)

    set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )

    if (MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
        )
    else ()
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror 
        )
    endif()

    # --- Testing (optional) -----------------------------------------------
    option(BUILD_TESTS "Enable building unit tests" ON)

    if(BUILD_TESTS)

    include(FetchContent)

    # Declare the external repo
    FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG        main   # or a specific commit hash / tag
    )


    enable_testing()

    set(GTEST_SUBMODULE_DIR ${CMAKE_SOURCE_DIR}/extern/googletest)
    if(EXISTS "${GTEST_SUBMODULE_DIR}/CMakeLists.txt")
        message(STATUS "Found googletest submodule at ${GTEST_SUBMODULE_DIR}; adding to build")
        add_subdirectory(${GTEST_SUBMODULE_DIR} EXCLUDE_FROM_ALL)
    else()
        message(STATUS "googletest not found in ${GTEST_SUBMODULE_DIR}. Fetching")
        FetchContent_MakeAvailable(gtest)
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE gtest)

    if(EXISTS "${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt")
        message(STATUS "tests/CMakeLists.txt found.")
        add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
    else()
        message(STATUS "No tests/CMakeLists.txt found; create tests/ to add unit tests.")
    endif()


    endif()