#[=======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Platform Library for Host
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Packages
--------

``PlatformLibrary::Host``
    Platform Library package for your host system

Dependencies
------------
``Beetree::Platform``
``Threads::Threads``
#]=======================================================================]

# cmake-format: off
if(NOT ${CMAKE_SYSTEM_PROCESSOR} STREQUAL ${CMAKE_HOST_SYSTEM_PROCESSOR}) 
    return()
endif()
# cmake-format: on

# External Packages
find_package(Threads)

# Create a static library for the host system
add_library(platform-library-host STATIC)
add_library(PlatformLibrary::Host ALIAS platform-library-host)

# Dependencies
# ------------
target_link_libraries(
    platform-library-host
    PUBLIC Beetree::Platform
    PRIVATE Threads::Threads
)
target_include_directories(
    platform-library-host
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)

# Source
# ------
target_sources(platform-library-host PRIVATE src/system-clock.cpp src/udp-send.cpp src/udp-receive.cpp)

# Install
# -------
install(TARGETS platform-library-host COMPONENT Development EXPORT Beetree)
install(DIRECTORY include/ TYPE INCLUDE COMPONENT Development)
