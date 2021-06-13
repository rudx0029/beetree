#[=======================================================================[.rst:

^^^^^^^^^^^^^^^^
STM32 Platform Library
^^^^^^^^^^^^^^^^

Platform convenience libraries for the STM32 microcontroller families

#]=======================================================================]
cmake_minimum_required(VERSION 3.15)
project(beetree LANGUAGES C CXX ASM VERSION 0.1.0.0)

# Policies
cmake_policy(SET CMP0076 NEW) # allow relative paths in target_sources
cmake_policy(SET CMP0077 NEW) # gtest pthreads behavior

# Options
# Change CMake's default value to enabled.
option(BEE_EXPORT_COMPILE_COMMANDS "Enable output of compile commands during generation." ON)
if(NOT DEFINED ENV{CMAKE_EXPORT_COMPILE_COMMANDS})
    set(CMAKE_EXPORT_COMPILE_COMMANDS ${BEE_EXPORT_COMPILE_COMMANDS})
endif()

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
    message(STATUS "[beetree-platform-stm32] Defaulting build type to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

find_package(BeetreePlatform REQUIRED)

add_subdirectory(stm32f0xx)
add_subdirectory(stm32f1xx)
add_subdirectory(stm32g0xx)
