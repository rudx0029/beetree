#[======================================================================[.rst:
#
# ^^^^^^^^^^^^^^^^^^^^^^^^
# Hello World! Application
# ^^^^^^^^^^^^^^^^^^^^^^^^
#
# The hello world application is a simple demonstration of the Beetree
# behavior tree API
#
# CMake File Format
# -----------------
# 1. Add Library - The library contains the business logic for the
#    application and is platform agnostic. Because it is platform agnostic,
#    it can be made available in a unit test environment, e.g. gtest executable
#
# 2. Add the sources for the library. These sources must be agnostic to the
#    platform. Platform sources will be added when creating the executable.
#
# 3. Link the library to any dependencies and add include directories
#
# 4. Add executables for each target platform - cross compiling.
#    The executable will link to the library and define a main to call in to
#    the library. These executables are what run on the target.
#
# 5. Install the helloworld library for developers and helloworld artifacts
#    to support BeeView
#
# 6. Add unit tests and unit test executable - when not cross compiling
#]======================================================================]

# 1. Application Library
# ----------------------
add_library(helloworld STATIC)
add_library(Helloworld::Helloworld ALIAS helloworld)

# 2. Source
# ---------
target_sources(
    helloworld
    PRIVATE
        src/install.cpp
        src/application.cpp
        src/helloworld-api.cpp
    PUBLIC
        include/helloworld/application.hpp
        include/helloworld/helloworld.tree
        include/helloworld/install.hpp
        include/helloworld/helloworld-api.hpp
        include/helloworld/helloworld-model.hpp
)

# 3. Dependencies
# --------------

target_include_directories(helloworld PUBLIC include)

target_link_libraries(
    helloworld PUBLIC Beetree::Beetree Beetree::StartPack Helloworld::Platform::Interface
)

# Registry and Tokens
# -------------------
include(BeeTreeAddTokens)
beetree_add_tokens(helloworld TOKENS ${CMAKE_CURRENT_SOURCE_DIR}/tokens.json)

include(BeeTreeAddRegistry)
beetree_add_registry(
    helloworld REGISTER_BANKS ${CMAKE_CURRENT_SOURCE_DIR}/registry/helloworld-register-bank.json
)

# 4.Targets and Platforms
# -----------------------
if(CMAKE_SYSTEM_PROCESSOR STREQUAL CMAKE_HOST_SYSTEM_PROCESSOR)
    add_subdirectory(targets/host)
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "cortex-m0")
    add_subdirectory(targets/stm32f030x8)
endif()

# 5. Install
# ----------

install(TARGETS helloworld COMPONENT helloworld-development)
install(
    DIRECTORY include/
    TYPE INCLUDE
    COMPONENT helloworld-development
)

include(BeeTreeInstallTokens)
beetree_install_tokens(helloworld)

include(BeeTreeInstallRegistry)
beetree_install_registry(helloworld)

# 6. Unit Tests
# -------------
if(BUILD_TESTING)
    # add the tests only for native builds
    # add_subdirectory(test) - no unit tests
endif()
