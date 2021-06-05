#[=======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Generic OS Platform Library 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Packages
--------

``Beetree::Platform::OS``
    Platform Library package for your host system

Dependencies
------------
``Beetree::Platform``
``Threads::Threads``
#]=======================================================================]
cmake_minimum_required(VERSION 3.15)
project(beetree-platform-os C CXX ASM)

# Policies
cmake_policy(SET CMP0076 NEW) # allow relative paths in target_sources
cmake_policy(SET CMP0077 NEW) # gtest pthreads behavior

# Options
option(BEE_BUILD_TESTING "Enable configuring and building BeeTree Platform OS unit tests" ON)
option(BEE_EXPORT_COMPILE_COMMANDS "Enable output of compile commands during generation." ON)
if(NOT DEFINED ENV{CMAKE_EXPORT_COMPILE_COMMANDS})
    set(CMAKE_EXPORT_COMPILE_COMMANDS ${BEE_EXPORT_COMPILE_COMMANDS})
endif()

# CMake Module Path
# list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

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
    message(STATUS "[BeeTree Platform OS] Defaulting build type to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(BEE_BUILD_TESTING)
    message(STATUS "[BeeTree Platform OS] Unit tests are enabled")
    include(CTest)
    enable_testing()
endif()

# External Packages
find_package(Threads)
find_package(BeetreePlatform)

# Create a static library for the host system
add_library(beetree-platform-os STATIC)
add_library(Beetree::Platform::OS ALIAS beetree-platform-os)

# Dependencies
# ------------
target_link_libraries(
    beetree-platform-os
    PUBLIC Beetree::Platform
    PRIVATE Threads::Threads
)
target_include_directories(
    beetree-platform-os
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)

# Source
# ------
target_sources(beetree-platform-os PRIVATE src/system-clock.cpp src/udp-send.cpp src/udp-receive.cpp)

# Install
# -------
install(TARGETS beetree-platform-os EXPORT BeetreePlatformOs)
install(
    EXPORT BeetreePlatformOs
    FILE BeetreePlatformOsConfig.cmake
    NAMESPACE Beetree::
    DESTINATION cmake
)
