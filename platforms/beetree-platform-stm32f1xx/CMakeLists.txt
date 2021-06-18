#[=======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Platform Library for STM32F1XX
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Packages
--------

``Beetree::Platform::stm32f1xx``
    Platform Library package for stm32f1xx series processors

Dependencies
------------

``Beetree::Platform``

.. note: The extensive directory structure is in order to expose the vendor's bsp
#]=======================================================================]


# Create an interface library for the stm32f1xx platforms
# This allows the client to consume the source and apply
# their compile definitions, linker options.
add_library(beetree-platform-stm32f1xx INTERFACE)
add_library(Beetree::Platform::stm32f1xx ALIAS beetree-platform-stm32f1xx)

# Dependencies
# ------------
# target_include_directories(beetree-platform-stm32f1xx INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
# target_include_directories(beetree-platform-stm32f1xx INTERFACE $<INSTALL_INTERFACE:src>)
target_link_libraries(beetree-platform-stm32f1xx INTERFACE Beetree::Platform)
target_include_directories(
    beetree-platform-stm32f1xx
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
    beetree-platform-stm32f1xx
    INTERFACE
        # build specs
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/system/system_stm32f1xx.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32f1xx_ll_utils.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32f1xx_ll_dma.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32f1xx_ll_gpio.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32f1xx_ll_usart.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32f1xx_ll_rcc.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32f1xx_ll_tim.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32f1xx_ll_exti.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/helpers.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-discrete-io.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-system-clock.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-serial-device-uart-dma.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-pwm.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-exti.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/serial-device-uart-dma.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/discrete-output.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/discrete-input.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/system-clock.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/pwm.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/counter.cpp>
        # install specs
        $<INSTALL_INTERFACE:src/system/system_stm32f1xx.c>
        $<INSTALL_INTERFACE:src/hal/stm32f1xx_ll_utils.c>
        $<INSTALL_INTERFACE:src/hal/stm32f1xx_ll_dma.c>
        $<INSTALL_INTERFACE:src/hal/stm32f1xx_ll_gpio.c>
        $<INSTALL_INTERFACE:src/hal/stm32f1xx_ll_usart.c>
        $<INSTALL_INTERFACE:src/hal/stm32f1xx_ll_rcc.c>
        $<INSTALL_INTERFACE:src/hal/stm32f1xx_ll_tim.c>
        $<INSTALL_INTERFACE:src/hal/stm32f1xx_ll_exti.c>
        $<INSTALL_INTERFACE:src/helpers.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-discrete-io.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-system-clock.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-serial-device-uart-dma.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-pwm.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-exti.cpp>
        $<INSTALL_INTERFACE:src/serial-device-uart-dma.cpp>
        $<INSTALL_INTERFACE:src/discrete-output.cpp>
        $<INSTALL_INTERFACE:src/discrete-input.cpp>
        $<INSTALL_INTERFACE:src/system-clock.cpp>
        $<INSTALL_INTERFACE:src/pwm.cpp>
        $<INSTALL_INTERFACE:src/counter.cpp>
)

# Install
# -------
install(
    TARGETS beetree-platform-stm32f1xx
    COMPONENT Development
    EXPORT Beetree
)
install(
    DIRECTORY include/
    TYPE INCLUDE
    COMPONENT Development
)
