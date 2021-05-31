#[=======================================================================[.rst:

^^^^^^^^^^^^^^^^
Platform Library
^^^^^^^^^^^^^^^^

STM32 common library providing common methods for all stm architectures

Packages
--------

``Beetree::Platform::STM32``
    Platform Library package for stm32f0xx series processors

#]=======================================================================]
add_library(beetree-platform-stm32 STATIC)
add_library(Beetree::Platform::STM32 ALIAS beetree-platform-stm32)

# Sources
# -------
target_sources(
    beetree-platform-stm32
    PRIVATE src/ring-q.c
)

# Dependencies
# ------------
target_include_directories(
    beetree-platform-stm32
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)

# Install
# -------
install(TARGETS beetree-platform-stm32 COMPONENT Development EXPORT Beetree)
install(DIRECTORY include/ TYPE INCLUDE COMPONENT Development)
