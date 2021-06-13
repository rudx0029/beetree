#[======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^^^^^^^^^
Beetree Platform
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Packages
--------

``Beetree::Platform``
    Header only library with interfaces integrating platform I/O

#]======================================================================]

cmake_minimum_required(VERSION 3.15)
project(beetree-platform LANGUAGES C CXX ASM VERSION 0.1.0.0)

# Policies
cmake_policy(SET CMP0076 NEW) # allow relative paths in target_sources
cmake_policy(SET CMP0077 NEW) # gtest pthreads behavior



# Options
# Change CMake's default value to enabled.
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

add_library(beetree-platform INTERFACE)
add_library(Beetree::Platform ALIAS beetree-platform)
set_target_properties(beetree-platform PROPERTIES EXPORT_NAME Platform)

# Dependencies
# ------------
target_include_directories(
    beetree-platform INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                               $<INSTALL_INTERFACE:include>
)

# Test
# ----
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

# Install
# -------

install(TARGETS beetree-platform EXPORT BeetreePlatform)
install(DIRECTORY include/ TYPE INCLUDE) # to export the include directory of an inteface library
install(
    EXPORT BeetreePlatform
    FILE BeetreePlatformConfig.cmake
    NAMESPACE Beetree::
    DESTINATION cmake
)
