#[=============================================================================[

Studio Bee
==========

A suite of software projects and libraries enabling small, lightweight, 
scalable embeddeded robotic systems. 

Beetree Platform

    The common interface between the Beetree Application and the hardware
    platform.

    Targets: 
    
    * ``Beetree::Platform``

Beetree
    The expressive and reactive behavior tree application framework for creating
    robotic motion and routines.

    Targets: 

    * ``Beetree::Beetree`` (core library)
    * ``Beetree::StartPack`` (basic behaviors and motions)
    * ``Beetree::TestAPI`` (unit test mocks and helpers)


Beetree Platform OS

    Generic OS Beetree Platform implementation which can be used as the basis
    for deploying your application on operating systems such as Linux, Windows,
    and Mac OS

    Targets:

    * ``Beetree::Platform::OS``

Minimal Application Topology
----------------------------

Your robotic system will be developed in to an Application component and a
Platform component. At the minimum the Application component needs to link to 
``Beetree::Beetree``. Your Platform component will need to link to 
``Beetree::Platform`` and implement the hardware interface. A pre-defined 
platform can be used, e.g. ``Beetree::Platform::OS`` or 
``Beetree::Platform::Stm32f0xx``, built upon, or a custom platform can be 
implemented. 

Build Options
-------------

``STUDIOBEE_BUILD_TESTING``
    Builds Beetree unit tests and create CTest targets. Default is ``ON``
  
#]=============================================================================]


cmake_minimum_required(VERSION 3.15)
project(studio-bee C CXX ASM)

#===============================================================================
# OPTIONS
#===============================================================================
option(STUDIOBEE_BUILD_TESTING "Enable configuring and building of Studio Bee unit tests" ON)

include(ExternalProject)

set(__studiobee_prefix ${CMAKE_CURRENT_BINARY_DIR}/studio-bee)
set(__studiobee_build ${__studiobee_prefix}/build)

# studio bee external projects logging settings
list(APPEND __studiobee_log_cmd 
    LOG_OUTPUT_ON_FAILURE ON 
    LOG_MERGED_STDOUTERR ON)

# helper method for adding studio bee imported targets
function(__studiobee_add_library target type bin_dir lib_name)
    add_library(${target} ${type} IMPORTED)
    set_target_properties(${target} PROPERTIES 
        INTERFACE_INCLUDE_DIRECTORIES ${bin_dir}/include
    )
    if(type STREQUAL "STATIC")
        set_target_properties(${target} PROPERTIES 
            IMPORTED_LOCATION ${BINARY_DIR}/lib/lib${lib_name}.a
        )
    endif()
endfunction()



#===============================================================================
# DEPENDENCIES
#
# ``Google Test`` / ``Google Mock``
#     Version 1.10.0 of Google's unit test framework. The dependency is only
#      downloaded and built if the option ``STUDIOBEE_BUILD_TESTING`` is ``ON``
#===============================================================================

if(STUDIOBEE_BUILD_TESTING)
    ExternalProject_Add(
        EP_GoogleTest
        PREFIX ${__studiobee_prefix}/googletest
        URL "${CMAKE_CURRENT_SOURCE_DIR}/application/thirdparty/googletest-release-1.10.0.tar.gz"
        URL_MD5 97c8d0b4e29aa4c663362b79ac2abc93
        BINARY_DIR ${__studiobee_build}/googletest
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${__studiobee_prefix}/googletest
        ${__studiobee_log_cmd}
    )
    ExternalProject_Get_Property(EP_GoogleTest BINARY_DIR)
    add_library(beetree_gtest UNKNOWN IMPORTED)
    set_target_properties(beetree_gtest PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${BINARY_DIR}/include
        IMPORTED_LOCATION ${BINARY_DIR}/lib/libgtest.a
    )
    add_dependencies(beetree_gtest EP_GoogleTest)

    add_library(beetree_gmock UNKNOWN IMPORTED)
    target_link_libraries(beetree_gmock INTERFACE beetree_gtest)
    set_target_properties(beetree_gmock PROPERTIES
        IMPORTED_LOCATION ${BINARY_DIR}/lib/libgmock.a
    )
endif()


#===============================================================================
# Studio Beetree
#===============================================================================

ExternalProject_Add(
    EP_BeetreePlatform
    PREFIX ${__studiobee_prefix}/beetree-platform
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/platform
    BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/platform/build
    BUILD_ALWAYS ON
    CMAKE_CACHE_ARGS
        -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX:STRING=${__studiobee_prefix}/beetree-platform
        -DBEE_BUILD_TESTING:BOOL=${STUDIOBEE_BUILD_TESTING}
        -DGTest_DIR:STRING=${__studiobee_prefix}/googletest/lib/cmake/GTest
    ${__studiobee_log_cmd}
)
if(STUDIOBEE_BUILD_TESTING)
    add_dependencies(EP_BeetreePlatform EP_GoogleTest)
endif()
ExternalProject_Get_Property(EP_BeetreePlatform BINARY_DIR)
__studiobee_add_library(Beetree::Platform INTERFACE ${BINARY_DIR} "")
add_dependencies(Beetree::Platform EP_BeetreePlatform)

ExternalProject_Add(
    EP_Beetree
    PREFIX ${__studiobee_prefix}/beetree
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/application
    BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/application/build
    BUILD_ALWAYS ON
    CMAKE_CACHE_ARGS
        -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX:STRING=${__studiobee_prefix}/beetree
        -DBEE_BUILD_TESTING:BOOL=${STUDIOBEE_BUILD_TESTING}
        -DBeetreePlatform_DIR:STRING=${__studiobee_prefix}/beetree-platform/cmake
        -DGTest_DIR:STRING=${__studiobee_prefix}/googletest/lib/cmake/GTest
    ${__studiobee_log_cmd}
)
add_dependencies(EP_Beetree EP_BeetreePlatform)
ExternalProject_Get_Property(EP_Beetree BINARY_DIR)

__studiobee_add_library(Beetree::Beetree STATIC ${BINARY_DIR} "beetree")
target_link_libraries(Beetree::Beetree INTERFACE Beetree::Platform)
add_dependencies(Beetree::Beetree EP_Beetree)

__studiobee_add_library(Beetree::StartPack STATIC ${BINARY_DIR} "beetree-start-pack")
target_link_libraries(Beetree::StartPack INTERFACE Beetree::Beetree)

if(STUDIOBEE_BUILD_TESTING)
    __studiobee_add_library(Beetree::TestAPI STATIC ${BINARY_DIR} "beetree-test-api")
    target_link_libraries(Beetree::TestAPI INTERFACE Beetree::Beetree beetree_gmock)
endif()


if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL ${CMAKE_HOST_SYSTEM_PROCESSOR} OR NOT CMAKE_TOOLCHAIN_FILE)     
    ExternalProject_Add(
        EP_BeetreePlatformOs
        PREFIX ${__studiobee_prefix}/beetree-platform-os
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/platform-os
        BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/platform-os/build
        BUILD_ALWAYS ON
        CMAKE_CACHE_ARGS
            -DCMAKE_INSTALL_PREFIX:STRING=${__studiobee_prefix}/beetree-platform-os
            -DBEE_BUILD_TESTING:BOOL=${STUDIOBEE_BUILD_TESTING}
            -DBeetreePlatform_DIR:STRING=${__studiobee_prefix}/beetree-platform/cmake
            -DGTest_DIR:STRING=${__studiobee_prefix}/googletest/lib/cmake/GTest
        ${__studiobee_log_cmd}
    )
    ExternalProject_Get_Property(EP_BeetreePlatformOs BINARY_DIR)
    add_dependencies(EP_BeetreePlatformOs EP_BeetreePlatform)
    
    __studiobee_add_library(Beetree::Platform::OS STATIC ${BINARY_DIR} "beetree-platform-os")
    target_link_libraries(Beetree::Platform::OS INTERFACE Beetree::Platform )
endif()
