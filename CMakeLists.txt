cmake_minimum_required(VERSION 3.15)
project(studio-bee LANGUAGES C CXX ASM VERSION 0.1.0.0)

# CMake Module Path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# C/C++ Standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Target Options
option(BEETREE_BUILD_TESTING "Build unit tests and test APIs for studiobee" ON)
option(BEETREE_BUILD_PLATFORM_OS "Build beetree-platform-os library for your host machine" ON)
option(BEETREE_BUILD_PLATFORM_STM32F0XX "Build beetree-platform-stm32f0xx library for your stm32f0xx target" ON)
option(BEETREE_BUILD_PLATFORM_STM32F1XX "Build beetree-platform-stm32f1xx library for your stm32f1xx target" ON)
option(BEETREE_BUILD_PLATFORM_STM32g0XX "Build beetree-platform-stm32g0xx library for your stm32g0xx target" ON)

# Toolchain Options
set(BEETREE_STM32F0XX_SYSTEM_PROCESSOR_TAG "cortex-m0" CACHE STRING "Set this tag to your stm32f0xx toolcahin file's CMAKE_SYSTEM_PROCESSOR")
set(BEETREE_STM32F1XX_SYSTEM_PROCESSOR_TAG "cortex-m3" CACHE STRING "Set this tag to your stm32f0xx toolcahin file's CMAKE_SYSTEM_PROCESSOR")
set(BEETREE_STM32G0XX_SYSTEM_PROCESSOR_TAG "cortex-m1+" CACHE STRING "Set this tag to your stm32f0xx toolcahin file's CMAKE_SYSTEM_PROCESSOR")

# force debug build type if not specified
# NOTE: This means that we will only support single configuration editors.
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "[BeeTree] Defaulting build type to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# configure unit testing if enabled
if(BEETREE_BUILD_TESTING AND ${CMAKE_SYSTEM_PROCESSOR} STREQUAL ${CMAKE_HOST_SYSTEM_PROCESSOR})
    message(STATUS "[BeeTree] Unit tests are enabled")
    include(cmake/gtest.cmake)
    include(CTest)
    enable_testing()
endif()

# studiobee main libraries
add_subdirectory(platforms/beetree-platform)
add_subdirectory(application)

# studiobee platforms
if(BEETREE_BUILD_PLATFORM_OS AND ${CMAKE_SYSTEM_PROCESSOR} STREQUAL ${CMAKE_HOST_SYSTEM_PROCESSOR})   
    add_subdirectory(platforms/beetree-platform-os)
endif()

if(BEETREE_BUILD_PLATFORM_STM32F0XX AND ${CMAKE_SYSTEM_PROCESSOR} MATCHES ${BEETREE_STM32F0XX_SYSTEM_PROCESSOR_TAG})
    add_subdirectory(platforms/beetree-platform-stm32f0xx)
endif()

if(BEETREE_BUILD_PLATFORM_STM32F1XX AND ${CMAKE_SYSTEM_PROCESSOR} MATCHES ${BEETREE_STM32F1XX_SYSTEM_PROCESSOR_TAG})
    add_subdirectory(platforms/beetree-platform-stm32f1xx)
endif()

if(BEETREE_BUILD_PLATFORM_STM32G0XX AND ${CMAKE_SYSTEM_PROCESSOR} MATCHES ${BEETREE_STM32G0XX_SYSTEM_PROCESSOR_TAG})
    add_subdirectory(platforms/beetree-platform-stm32g0xx)
endif()

