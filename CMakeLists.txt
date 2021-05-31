cmake_minimum_required(VERSION 3.14)
project(beetree C CXX ASM)

# Policies
cmake_policy(SET CMP0076 NEW) # allow relative paths in target_sources
cmake_policy(SET CMP0077 NEW) # gtest pthreads behavior

# Options
# Change CMake's default value to enabled.
option(BEETREE_BUILD_EXAMPLES "Enable configuring and building BeeTree example applications" OFF)
option(BEETREE_BUILD_TESTING "Enable configuring and building BeeTree unit tests" ON)
option(BEETREE_EXPORT_COMPILE_COMMANDS "Enable output of compile commands during generation." ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ${BEETREE_EXPORT_COMPILE_COMMANDS})

# CMake Module Path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# C/C++ Standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# force debug build type if not specified
# NOTE: This means that we will only support single configuration editors.
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "[BeeTree] Defaulting build type to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(BEETREE_BUILD_TESTING AND (CMAKE_SYSTEM_PROCESSOR STREQUAL CMAKE_HOST_SYSTEM_PROCESSOR))
    message(STATUS "[BeeTree] Unit tests are enabled")
    include(CTest)
    include(FetchGTest)
    enable_testing()
endif()

install(
    EXPORT Beetree
    NAMESPACE Beetree::
    DESTINATION cmake
    COMPONENT Development
)

add_subdirectory(application/core)
add_subdirectory(application/startpk)
add_subdirectory(application/experimental)
add_subdirectory(platform)
add_subdirectory(tools/beeview)

if(BUILD_TESTING)
    message(STATUS "[BeeTree] Configuring unit tests")
endif()
