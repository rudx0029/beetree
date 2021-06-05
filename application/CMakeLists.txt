cmake_minimum_required(VERSION 3.15)
project(beetree C CXX ASM)

# Policies
cmake_policy(SET CMP0076 NEW) # allow relative paths in target_sources
cmake_policy(SET CMP0077 NEW) # gtest pthreads behavior

# Options
# Change CMake's default value to enabled.
option(BEETREE_BUILD_EXAMPLES "Enable configuring and building BeeTree example applications" OFF)
option(BEE_BUILD_TESTING "Enable configuring and building BeeTree unit tests" ON)
option(BEE_EXPORT_COMPILE_COMMANDS "Enable output of compile commands during generation." ON)
if(NOT DEFINED ENV{CMAKE_EXPORT_COMPILE_COMMANDS})
    set(CMAKE_EXPORT_COMPILE_COMMANDS ${BEE_EXPORT_COMPILE_COMMANDS})
endif()
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

if(BEE_BUILD_TESTING AND (CMAKE_SYSTEM_PROCESSOR STREQUAL CMAKE_HOST_SYSTEM_PROCESSOR))
    message(STATUS "[BeeTree] Unit tests are enabled")
    include(CTest)
    enable_testing()
endif()


find_package(BeetreePlatform REQUIRED)

add_subdirectory(core)
add_subdirectory(startpk)
add_subdirectory(experimental)

install(
    EXPORT Beetree
    FILE BeetreeConfig.cmake
    NAMESPACE Beetree::
    DESTINATION cmake
)