#[======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^^^^^^^^^
Beetree Platforms Interface
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Packages
--------

``Beetree::Platform::Interface``
    Header only library with interfaces integrating platform I/O

#]======================================================================]
add_library(beetree-platform INTERFACE)
add_library(Beetree::Platform::Interface ALIAS beetree-platform)
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
install(
    TARGETS beetree-platform
    EXPORT Beetree
    PUBLIC_HEADER DESTINATION include COMPONENT Development
)
install(
    DIRECTORY include/
    TYPE INCLUDE
    COMPONENT Development
)
