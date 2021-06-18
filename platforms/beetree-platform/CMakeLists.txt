#[======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^^^^^^^^^
Beetree Platform
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Packages
--------

``Beetree::Platform``
    Header only library with interfaces integrating platform I/O

#]======================================================================]

add_library(beetree-platform INTERFACE)
add_library(Beetree::Platform ALIAS beetree-platform)
set_target_properties(beetree-platform PROPERTIES EXPORT_NAME Platform)

# Dependencies
# ------------
target_include_directories(
    beetree-platform INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                               $<INSTALL_INTERFACE:include>
)

# Test
# ----
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

# Install
# -------

install(TARGETS beetree-platform EXPORT BeetreePlatform)
install(DIRECTORY include/ TYPE INCLUDE) # to export the include directory of an inteface library
install(
    EXPORT BeetreePlatform
    FILE BeetreePlatformConfig.cmake
    NAMESPACE Beetree::
    DESTINATION cmake
)
