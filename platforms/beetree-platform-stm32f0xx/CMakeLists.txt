#[=======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Platform Library for STM32F0XX
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Packages
--------

``Beetree::Platform::stm32f0xx``
    Platform Library package for stm32f0xx series processors

Dependencies
------------

``Beetree::Platform``

.. note: The extensive directory structure is in order to expose the vendor's bsp
#]=======================================================================]
cmake_minimum_required(VERSION 3.15)
project(beetree-platform-stm32f0xx LANGUAGES C CXX ASM VERSION 0.1.0.0)

# Policies
cmake_policy(SET CMP0076 NEW) # allow relative paths in target_sources

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
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# force debug build type if not specified
# NOTE: This means that we will only support single configuration editors.
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "[beetree-platform-stm32] Defaulting build type to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

find_package(BeetreePlatform REQUIRED)

# Create an interface library for the stm32f0xx platforms
# This allows the client to consume the source and apply
# their compile definitions, linker options.
add_library(beetree-platform-stm32f0xx INTERFACE)
add_library(Beetree::Platform::stm32f0xx ALIAS beetree-platform-stm32f0xx)

# Dependencies
# ------------
# target_include_directories(beetree-platform-stm32f0xx INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
# target_include_directories(beetree-platform-stm32f0xx INTERFACE $<INSTALL_INTERFACE:src>)
target_link_libraries(beetree-platform-stm32f0xx INTERFACE Beetree::Platform)
target_include_directories(
    beetree-platform-stm32f0xx
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        # expose the vendor's bsp
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/Legacy>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/system>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/cmsis>
        $<INSTALL_INTERFACE:src>
        $<INSTALL_INTERFACE:src/hal>
        $<INSTALL_INTERFACE:src/hal/Legacy>
        $<INSTALL_INTERFACE:src/system>
        $<INSTALL_INTERFACE:src/cmsis>
)

# Source
# ------
target_sources(
    beetree-platform-stm32f0xx
    INTERFACE
        # build specs
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/system/system_stm32f0xx.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/hal/stm32f0xx_ll_utils.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/hal/stm32f0xx_ll_adc.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/hal/stm32f0xx_ll_dma.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/hal/stm32f0xx_ll_exti.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/hal/stm32f0xx_ll_gpio.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/hal/stm32f0xx_ll_usart.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/hal/stm32f0xx_ll_rcc.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/hal/stm32f0xx_ll_tim.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/hal/stm32f0xx_ll_i2c.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/hal/stm32f0xx_ll_spi.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/helpers.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/boot/boot-discrete-io.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/boot/boot-system-clock.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/boot/boot-serial-device-uart-dma.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/boot/boot-serial-device-i2c.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/boot/boot-pwm.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/boot/boot-exti.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/boot/boot-counter.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/serial-device-uart-dma.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/serial-device-i2c.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/i-serial-driver.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/bno055-imu-device.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/discrete-output.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/discrete-input.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/system-clock.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/pwm.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f0xx/counter.cpp>
        # install specs
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/system/system_stm32f0xx.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/hal/stm32f0xx_ll_utils.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/hal/stm32f0xx_ll_dma.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/hal/stm32f0xx_ll_exti.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/hal/stm32f0xx_ll_gpio.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/hal/stm32f0xx_ll_usart.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/hal/stm32f0xx_ll_rcc.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/hal/stm32f0xx_ll_tim.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/hal/stm32f0xx_ll_i2c.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/hal/stm32f0xx_ll_spi.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/helpers.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/boot/boot-discrete-io.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/boot/boot-system-clock.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/boot/boot-serial-device-uart-dma.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/boot/boot-serial-device-i2c.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/boot/boot-pwm.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/boot/boot-exti.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/boot/boot-counter.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/serial-device-uart-dma.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/serial-device-i2c.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/i-serial-driver.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/bno055-imu-device.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/discrete-output.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/discrete-input.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/system-clock.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/pwm.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f0xx/counter.cpp>
)

# Install
# -------
install(
    TARGETS beetree-platform-stm32f0xx
    COMPONENT Development
    EXPORT Beetree
)
install(
    DIRECTORY include/
    TYPE INCLUDE
    COMPONENT Development
)