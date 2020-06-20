#[======================================================================[.rst:

^^^^^^^^^^^^
Hello World!
^^^^^^^^^^^^

Hello World! platform for the stm32f030x8 microcontroller

Depndencies
-----------

* Beetree::Platform::Interface
* Helloworld::Platform::Interface
* PlatformLibrary::Core
* PlatformLibrary for stm32f0xx

Result Package
--------------

``Helloworld::Platform::Stm32f030x8``
    Hello world! platform package for the stm32f030x8

``helloworld-plt-stm32f030x8``
    Hello world! platform library for the stm32f030x8

#]======================================================================]

add_library(helloworld-plt-stm32f030x8 STATIC)
add_library(Helloworld::Platform::Stm32f030x8 ALIAS helloworld-plt-stm32f030x8)

# Sources
# -------
target_sources(
    helloworld-plt-stm32f030x8 PRIVATE boot.cpp interrupt-handlers.cpp internal-platform.cpp
                                       internal-platform.hpp startup_stm32f030x8.s
)

# Dependencies
# ------------
target_link_libraries(
    helloworld-plt-stm32f030x8
    PUBLIC Beetree::Platform::Interface Helloworld::Platform::Interface
    PRIVATE PlatformLibrary::Stm32f0xx
)

# configure the stm firmware
target_compile_definitions(
    helloworld-plt-stm32f030x8
    PRIVATE STM32F030x8
            USE_FULL_LL_DRIVER
            # HAL System Clock/RCC Configuration Overrides
            HSE_VALUE=8000000
            HSE_STARTUP_TIMEOUT=100
            LSE_STARTUP_TIMEOUT=5000
            LSE_VALUE=32768
            HSI_VALUE=8000000
            LSI_VALUE=40000
            # HAL System Configuration Overrides
            VDD_VALUE=3300
            PREFETCH_ENABLE=1
            INSTRUCTION_CACHE_ENABLE=0
            DATA_CACHE_ENABLE=0
)

target_link_options(
    helloworld-plt-stm32f030x8 INTERFACE "-T${CMAKE_CURRENT_SOURCE_DIR}/STM32F030R8Tx_FLASH.ld"
)

# Install
# -------
install(TARGETS helloworld-plt-stm32f030x8 COMPONENT helloworld-development)
