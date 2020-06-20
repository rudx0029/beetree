#[=======================================================================[.rst:

^^^^^^^^^^^^^^^^
Platform Library
^^^^^^^^^^^^^^^^

Core library providing common methods for all platforms. Platforms libraries
specific to a architecture should link to this library.

Packages
--------

``PlatformLibrary::Core``
    Platform Library package for stm32f0xx series processors

#]=======================================================================]
add_library(platform-library STATIC)
add_library(PlatformLibrary::Core ALIAS platform-library)

# Sources
# -------
target_sources(
    platform-library
    PRIVATE src/ring-q.c
)

# Dependencies
# ------------
target_include_directories(
    platform-library
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)

# Install
# -------
install(TARGETS platform-library COMPONENT Development EXPORT Beetree)
install(DIRECTORY include/ TYPE INCLUDE COMPONENT Development)
