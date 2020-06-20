#[=======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Platform Library for STM32F1XX
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Packages
--------

``PlatformLibrary::Stm32f1xx``
    Platform Library package for stm32f1xx series processors

Dependencies
------------

``PlatformLibrary::Core``

.. note: The extensive directory structure is in order to expose the vendor's bsp
#]=======================================================================]

if(NOT CMAKE_SYSTEM_PROCESSOR STREQUAL "cortex-m3")
    return()
endif()

# C/C++ Standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Create an interface library for the stm32f1xx platforms
# This allows the client to consume the source and apply
# their compile definitions, linker options.
add_library(platform-library-stm32f1xx INTERFACE)
add_library(PlatformLibrary::Stm32f1xx ALIAS platform-library-stm32f1xx)

# Dependencies
# ------------
# target_include_directories(platform-library-stm32f1xx INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
# target_include_directories(platform-library-stm32f1xx INTERFACE $<INSTALL_INTERFACE:src>)
target_link_libraries(platform-library-stm32f1xx INTERFACE PlatformLibrary::Core)
target_include_directories(
    platform-library-stm32f1xx
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        # expose the vendor's bsp
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/hal>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/hal/Legacy>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/system>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/cmsis>
        $<INSTALL_INTERFACE:src>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/hal>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/hal/Legacy>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/system>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/cmsis>
)

# Source
# ------
target_sources(
    platform-library-stm32f1xx
    INTERFACE
        # build specs
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/system/system_stm32f1xx.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/hal/stm32f1xx_ll_utils.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/hal/stm32f1xx_ll_dma.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/hal/stm32f1xx_ll_gpio.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/hal/stm32f1xx_ll_usart.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/hal/stm32f1xx_ll_rcc.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/hal/stm32f1xx_ll_tim.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/hal/stm32f1xx_ll_exti.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/helpers.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/boot/boot-discrete-io.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/boot/boot-system-clock.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/boot/boot-serial-device-uart-dma.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/boot/boot-pwm.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/boot/boot-exti.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/serial-device-uart-dma.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/discrete-output.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/discrete-input.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/system-clock.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/pwm.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/platform-library/stm32f1xx/counter.cpp>
        # install specs
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/system/system_stm32f1xx.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/hal/stm32f1xx_ll_utils.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/hal/stm32f1xx_ll_dma.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/hal/stm32f1xx_ll_gpio.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/hal/stm32f1xx_ll_usart.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/hal/stm32f1xx_ll_rcc.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/hal/stm32f1xx_ll_tim.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/hal/stm32f1xx_ll_exti.c>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/helpers.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/boot/boot-discrete-io.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/boot/boot-system-clock.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/boot/boot-serial-device-uart-dma.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/boot/boot-pwm.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/boot/boot-exti.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/serial-device-uart-dma.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/discrete-output.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/discrete-input.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/system-clock.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/pwm.cpp>
        $<INSTALL_INTERFACE:src/platform-library/stm32f1xx/counter.cpp>
)

# Install
# -------
install(
    TARGETS platform-library-stm32f1xx
    COMPONENT Development
    EXPORT Beetree
)
install(
    DIRECTORY include/
    TYPE INCLUDE
    COMPONENT Development
)
