#[=======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Generic OS Platform Library 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Packages
--------

``Beetree::Platform::OS``
    Platform Library package for your host system

Dependencies
------------
``Beetree::Platform``
``Threads::Threads``
#]=======================================================================]

# External Packages
find_package(Threads)

# Create a static library for the host system
add_library(beetree-platform-os STATIC)
add_library(Beetree::Platform::OS ALIAS beetree-platform-os)

# Dependencies
# ------------
target_link_libraries(
    beetree-platform-os
    PUBLIC Beetree::Platform
    PRIVATE Threads::Threads
)
target_include_directories(
    beetree-platform-os
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)

# Source
# ------
target_sources(beetree-platform-os PRIVATE src/system-clock.cpp src/udp-send.cpp src/udp-receive.cpp)

# Install
# -------
install(TARGETS beetree-platform-os EXPORT BeetreePlatformOs)
install(DIRECTORY include/ TYPE INCLUDE)
install(
    EXPORT BeetreePlatformOs
    FILE BeetreePlatformOsConfig.cmake
    NAMESPACE Beetree::
    DESTINATION cmake
)
