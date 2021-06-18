#[=======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Platform Library for STM32g0XX
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Packages
--------

``Beetree::Platform::stm32g0xx``
    Platform Library package for stm32g0xx series processors

Dependencies
------------

``Beetree::Platform``

.. note: The extensive directory structure is in order to expose the vendor's bsp
#]=======================================================================]

# Create an interface library for the stm32g0xx platforms
# This allows the client to consume the source and apply
# their compile definitions, linker options.
add_library(beetree-platform-stm32g0xx INTERFACE)
add_library(Beetree::Platform::stm32g0xx ALIAS beetree-platform-stm32g0xx)

# Dependencies
# ------------
target_link_libraries(beetree-platform-stm32g0xx INTERFACE Beetree::Platform)
target_include_directories(
    beetree-platform-stm32g0xx
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
    beetree-platform-stm32g0xx
    INTERFACE
        # build specs
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/system/system_stm32g0xx.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32g0xx_ll_utils.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32g0xx_ll_adc.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32g0xx_ll_dma.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32g0xx_ll_exti.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32g0xx_ll_gpio.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32g0xx_ll_usart.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32g0xx_ll_rcc.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32g0xx_ll_tim.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32g0xx_ll_i2c.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/hal/stm32g0xx_ll_spi.c>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/helpers.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-discrete-io.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-system-clock.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-serial-device-uart-dma.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-serial-device-i2c.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-pwm.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-exti.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/boot/boot-counter.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/serial-device-uart-dma.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/serial-device-i2c.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/i-serial-driver.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/bno055-imu-device.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/discrete-output.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/discrete-input.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/system-clock.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/pwm.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/counter.cpp>
        # install specs
        $<INSTALL_INTERFACE:src/system/system_stm32g0xx.c>
        $<INSTALL_INTERFACE:src/hal/stm32g0xx_ll_utils.c>
        $<INSTALL_INTERFACE:src/hal/stm32g0xx_ll_dma.c>
        $<INSTALL_INTERFACE:src/hal/stm32g0xx_ll_exti.c>
        $<INSTALL_INTERFACE:src/hal/stm32g0xx_ll_gpio.c>
        $<INSTALL_INTERFACE:src/hal/stm32g0xx_ll_usart.c>
        $<INSTALL_INTERFACE:src/hal/stm32g0xx_ll_rcc.c>
        $<INSTALL_INTERFACE:src/hal/stm32g0xx_ll_tim.c>
        $<INSTALL_INTERFACE:src/hal/stm32g0xx_ll_i2c.c>
        $<INSTALL_INTERFACE:src/hal/stm32g0xx_ll_spi.c>
        $<INSTALL_INTERFACE:src/helpers.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-discrete-io.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-system-clock.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-serial-device-uart-dma.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-serial-device-i2c.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-pwm.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-exti.cpp>
        $<INSTALL_INTERFACE:src/boot/boot-counter.cpp>
        $<INSTALL_INTERFACE:src/serial-device-uart-dma.cpp>
        $<INSTALL_INTERFACE:src/serial-device-i2c.cpp>
        $<INSTALL_INTERFACE:src/i-serial-driver.cpp>
        $<INSTALL_INTERFACE:src/bno055-imu-device.cpp>
        $<INSTALL_INTERFACE:src/discrete-output.cpp>
        $<INSTALL_INTERFACE:src/discrete-input.cpp>
        $<INSTALL_INTERFACE:src/system-clock.cpp>
        $<INSTALL_INTERFACE:src/pwm.cpp>
        $<INSTALL_INTERFACE:src/counter.cpp>
)

# Install
# -------
install(
    TARGETS beetree-platform-stm32g0xx
    COMPONENT Development
    EXPORT Beetree
)
install(
    DIRECTORY include/
    TYPE INCLUDE
    COMPONENT Development
)
