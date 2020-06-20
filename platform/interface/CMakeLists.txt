#[======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^^^^^^^^^
Beetree Platforms Interface
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Packages
--------

``Beetree::Platform::Interface``
    Header only library with interfaces integrating platform I/O

#]======================================================================]
add_library(beetree-plt-interface INTERFACE)
add_library(Beetree::Platform::Interface ALIAS beetree-plt-interface)
set_target_properties(beetree-plt-interface PROPERTIES EXPORT_NAME Platform::Interface)

# Dependencies
# ------------
target_include_directories(
    beetree-plt-interface
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)

# Install
# -------
install(TARGETS beetree-plt-interface EXPORT Beetree PUBLIC_HEADER DESTINATION include COMPONENT Development)
install(DIRECTORY include/ TYPE INCLUDE COMPONENT Development)
