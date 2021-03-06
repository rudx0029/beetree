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

``STUDIOBEE_STM32F0XX_SYSTEM_PROCESSOR_TAG``
    Expected toolchain's system processor name enabling 
    ``beetree-platform-stm32f0xx`` library

``STUDIOBEE_STM32F1XX_SYSTEM_PROCESSOR_TAG``
    Expected toolchain's system processor name enabling 
    ``beetree-platform-stm32f1xx`` library

``STUDIOBEE_STM32G0XX_SYSTEM_PROCESSOR_TAG``
    Expected toolchain's system processor name enabling 
    ``beetree-platform-stm32g0xx`` library
  
#]=============================================================================]


cmake_minimum_required(VERSION 3.15)

#===============================================================================
# OPTIONS
#===============================================================================
if(NOT DEFINED STUDIOBEE_BUILD_TESTING)
    set(STUDIOBEE_BUILD_TESTING ON)
endif()
if(NOT STUDIOBEE_STM32F0XX_SYSTEM_PROCESSOR_TAG)
    set(STUDIOBEE_STM32F0XX_SYSTEM_PROCESSOR_TAG "cortex-m0")
endif()
if(NOT STUDIOBEE_STM32F1XX_SYSTEM_PROCESSOR_TAG)
    set(STUDIOBEE_STM32F1XX_SYSTEM_PROCESSOR_TAG "cortex-m3")
endif()
if(NOT STUDIOBEE_STM32G0XX_SYSTEM_PROCESSOR_TAG) 
    set(STUDIOBEE_STM32G0XX_SYSTEM_PROCESSOR_TAG "cortex-m0+")
endif()

include(ExternalProject)

set(__studiobee_prefix ${CMAKE_CURRENT_BINARY_DIR}/studio-bee)
set(__studiobee_build ${__studiobee_prefix}/build)

# studio bee external projects logging settings
list(APPEND __studiobee_log_cmd
    LOG_BUILD ON
    LOG_OUTPUT_ON_FAILURE ON 
    LOG_MERGED_STDOUTERR ON)

# helper method for adding studio bee imported targets
function(__studiobee_add_library target type bin_dir lib_name)
    add_library(${target} ${type} IMPORTED)
    set_target_properties(${target} PROPERTIES 
        INTERFACE_INCLUDE_DIRECTORIES ${bin_dir}/include
    )
    file (MAKE_DIRECTORY ${bin_dir}/include)
    if(type STREQUAL "STATIC")
        file (MAKE_DIRECTORY ${bin_dir}/lib)
        file (TOUCH ${bin_dir}/lib/lib${lib_name}.a)
        set_target_properties(${target} PROPERTIES 
            IMPORTED_LOCATION ${bin_dir}/lib/lib${lib_name}.a
        )
    endif()
endfunction()


#===============================================================================
# Studio Bee Repo
# 
# First, download the repo but do not configure it or build it
#===============================================================================
if(NOT PROJECT_NAME STREQUAL "studio-bee" AND NOT STUDIOBEE_SOURCE_DIR)
    set(__studiobee_git_repo https://github.com/temple-mountain-robotics/beetree.git)
    set(__studiobee_source_dir ${__studiobee_prefix}/src)

    ExternalProject_Add(
        EP_StudioBee    
        PREFIX ${__studiobee_prefix}
        GIT_REPOSITORY ${__studiobee_git_repo}   
        GIT_SHALLOW ON
        SOURCE_DIR ${__studiobee_source_dir}
        CONFIGURE_COMMAND "" # disable all other steps
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )
elseif(STUDIOBEE_SOURCE_DIR)    
    set(__studiobee_source_dir ${STUDIOBEE_SOURCE_DIR})
else()
    set(__studiobee_source_dir ${CMAKE_CURRENT_SOURCE_DIR})
endif()

#===============================================================================
# DEPENDENCIES
#
# Configure and build any dependencies
#
# ``Google Test`` / ``Google Mock``
#     Version 1.10.0 of Google's unit test framework. The dependency is only
#      downloaded and built if the option ``STUDIOBEE_BUILD_TESTING`` is ``ON``
#===============================================================================

if(STUDIOBEE_BUILD_TESTING)
    if(TARGET EP_StudioBee)
        list(APPEND __studiobee_deps DEPENDS EP_StudioBee)
    endif()

    ExternalProject_Add(
        EP_GoogleTest
        PREFIX ${__studiobee_prefix}/googletest
        URL "${__studiobee_source_dir}/application/thirdparty/googletest-release-1.10.0.tar.gz"
        #URL_MD5 97c8d0b4e29aa4c663362b79ac2abc93
        BINARY_DIR ${__studiobee_build}/googletest
        DEPENDS ${__studiobee_deps}
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
# Studio Bee Projects
#
# Finally, configure and build each project in the StudioBee repo
#===============================================================================

set(__studiobee_deps "")
if(TARGET EP_StudioBee OR STUDIOBEE_BUILD_TESTING)
    set(__studiobee_deps DEPENDS)
    if(TARGET EP_StudioBee)
        list(APPEND __studiobee_deps EP_StudioBee)
    endif()
    if(STUDIOBEE_BUILD_TESTING)
        list(APPEND __studiobee_deps EP_GoogleTest)
    endif()
endif()

ExternalProject_Add(
    EP_BeetreePlatform
    PREFIX ${__studiobee_prefix}/beetree-platform
    SOURCE_DIR ${__studiobee_source_dir}/platforms/beetree-platform
    BINARY_DIR ${__studiobee_build}/beetree-platform
    INSTALL_DIR ${__studiobee_prefix}/beetree-platform
    ${__studiobee_deps}
    BUILD_ALWAYS ON
    CMAKE_CACHE_ARGS
        -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX:STRING=${__studiobee_prefix}/beetree-platform
        -DBEE_BUILD_TESTING:BOOL=${STUDIOBEE_BUILD_TESTING}
        -DGTest_DIR:STRING=${__studiobee_prefix}/googletest/lib/cmake/GTest
    ${__studiobee_log_cmd}
)
ExternalProject_Get_Property(EP_BeetreePlatform BINARY_DIR SOURCE_DIR INSTALL_DIR)
__studiobee_add_library(Beetree::Platform INTERFACE ${INSTALL_DIR} "")
add_dependencies(Beetree::Platform EP_BeetreePlatform)

ExternalProject_Add(
    EP_Beetree
    PREFIX ${__studiobee_prefix}/beetree
    SOURCE_DIR ${__studiobee_source_dir}/application
    BINARY_DIR ${__studiobee_build}/beetree
    INSTALL_DIR ${__studiobee_prefix}/beetree
    BUILD_ALWAYS ON
    DEPENDS EP_BeetreePlatform
    CMAKE_CACHE_ARGS
        -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX:STRING=${__studiobee_prefix}/beetree
        -DBEE_BUILD_TESTING:BOOL=${STUDIOBEE_BUILD_TESTING}
        -DBeetreePlatform_DIR:STRING=${__studiobee_prefix}/beetree-platform/cmake
        -DGTest_DIR:STRING=${__studiobee_prefix}/googletest/lib/cmake/GTest
    ${__studiobee_log_cmd}
)
ExternalProject_Get_Property(EP_Beetree BINARY_DIR SOURCE_DIR INSTALL_DIR)
set(beetree_SOURCE_DIR ${SOURCE_DIR})
set(beetree_BINARY_DIR ${BINARY_DIR})
set(beetree_INSTALL_DIR ${INSTALL_DIR})

__studiobee_add_library(Beetree::Beetree STATIC ${INSTALL_DIR} "beetree")
target_link_libraries(Beetree::Beetree INTERFACE Beetree::Platform)
add_dependencies(Beetree::Beetree EP_Beetree)

__studiobee_add_library(Beetree::StartPack STATIC ${INSTALL_DIR} "beetree-start-pack")
target_link_libraries(Beetree::StartPack INTERFACE Beetree::Beetree)
add_dependencies(Beetree::StartPack EP_Beetree)

__studiobee_add_library(Beetree::Experimental STATIC ${INSTALL_DIR} "beetree-experimental")
target_link_libraries(Beetree::Experimental INTERFACE Beetree::Beetree)

if(STUDIOBEE_BUILD_TESTING)
    __studiobee_add_library(Beetree::TestAPI STATIC ${INSTALL_DIR} "beetree-test-api")
    target_link_libraries(Beetree::TestAPI INTERFACE Beetree::Beetree beetree_gmock)
endif()


if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL ${CMAKE_HOST_SYSTEM_PROCESSOR} AND NOT CMAKE_TOOLCHAIN_FILE)     
    ExternalProject_Add(
        EP_BeetreePlatformOs
        PREFIX ${__studiobee_prefix}/beetree-platform-os
        SOURCE_DIR ${__studiobee_source_dir}/platforms/beetree-platform-os
        BINARY_DIR ${__studiobee_build}/beetree-platform-os
        INSTALL_DIR ${__studiobee_prefix}/beetree-platform-os
        BUILD_ALWAYS ON
        DEPENDS EP_BeetreePlatform
        CMAKE_CACHE_ARGS
            -DCMAKE_INSTALL_PREFIX:STRING=${__studiobee_prefix}/beetree-platform-os
            -DBEE_BUILD_TESTING:BOOL=${STUDIOBEE_BUILD_TESTING}
            -DBeetreePlatform_DIR:STRING=${__studiobee_prefix}/beetree-platform/cmake
            -DGTest_DIR:STRING=${__studiobee_prefix}/googletest/lib/cmake/GTest
        ${__studiobee_log_cmd}
    )
    ExternalProject_Get_Property(EP_BeetreePlatformOs BINARY_DIR SOURCE_DIR INSTALL_DIR)    
    __studiobee_add_library(Beetree::Platform::OS STATIC ${INSTALL_DIR} "beetree-platform-os")
    target_link_libraries(Beetree::Platform::OS INTERFACE Beetree::Platform )
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES ${STUDIOBEE_STM32F0XX_SYSTEM_PROCESSOR_TAG})
    ExternalProject_Add(
        EP_BeetreePlatformStm32f0xx
        PREFIX ${__studiobee_prefix}/beetree-platform-stm32f0xx
        SOURCE_DIR ${__studiobee_source_dir}/platforms/beetree-platform-stm32f0xx
        BINARY_DIR ${__studiobee_build}/beetree-platform-stm32f0xx
        INSTALL_DIR ${__studiobee_prefix}/beetree-platform-stm32f0xx
        BUILD_ALWAYS ON
        DEPENDS EP_BeetreePlatform
        CMAKE_CACHE_ARGS
            -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
            -DCMAKE_INSTALL_PREFIX:STRING=${__studiobee_prefix}/beetree-platform-stm32f0xx
            -DBeetreePlatform_DIR:STRING=${__studiobee_prefix}/beetree-platform/cmake
        ${__studiobee_log_cmd}
    )
    ExternalProject_Get_Property(EP_BeetreePlatformStm32f0xx BINARY_DIR)
    __studiobee_add_library(Beetree::Platform::stm32f0xx STATIC ${BINARY_DIR} "beetree-platform-stm32f0xx")
    target_link_libraries(Beetree::Platform::stm32f0xx INTERFACE Beetree::Platform )
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES ${STUDIOBEE_STM32F1XX_SYSTEM_PROCESSOR_TAG})
    ExternalProject_Add(
        EP_BeetreePlatformStm32f1xx
        PREFIX ${__studiobee_prefix}/beetree-platform-stm32f1xx
        SOURCE_DIR ${__studiobee_source_dir}/platforms/beetree-platform-stm32f1xx
        BINARY_DIR ${__studiobee_build}/beetree-platform-stm32f1xx
        INSTALL_DIR ${__studiobee_prefix}/beetree-platform-stm32f1xx
        BUILD_ALWAYS ON
        DEPENDS EP_BeetreePlatform
        CMAKE_CACHE_ARGS
            -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
            -DCMAKE_INSTALL_PREFIX:STRING=${__studiobee_prefix}/beetree-platform-stm32f1xx
            -DBeetreePlatform_DIR:STRING=${__studiobee_prefix}/beetree-platform/cmake
        ${__studiobee_log_cmd}
    )
    ExternalProject_Get_Property(EP_BeetreePlatformStm32f1xx BINARY_DIR)
    add_dependencies(EP_BeetreePlatformStm32f1xx EP_BeetreePlatform)

    __studiobee_add_library(Beetree::Platform::stm32f1xx STATIC ${BINARY_DIR} "beetree-platform-stm32f1xx")
    target_link_libraries(Beetree::Platform::stm32f1xx INTERFACE Beetree::Platform )
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES ${STUDIOBEE_STM32G0XX_SYSTEM_PROCESSOR_TAG})
    ExternalProject_Add(
        EP_BeetreePlatformStm32g0xx
        PREFIX ${__studiobee_prefix}/beetree-platform-stm32g0xx
        SOURCE_DIR ${__studiobee_source_dir}/platforms/beetree-platform-stm32g0xx
        BINARY_DIR ${__studiobee_build}/beetree-platform-stm32g0xx
        INSTALL_DIR ${__studiobee_prefix}/beetree-platform-stm32g0xx
        BUILD_ALWAYS ON
        CMAKE_CACHE_ARGS
            -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
            -DCMAKE_INSTALL_PREFIX:STRING=${__studiobee_prefix}/beetree-platform-stm32g0xx
            -DBeetreePlatform_DIR:STRING=${__studiobee_prefix}/beetree-platform/cmake
        ${__studiobee_log_cmd}
    )
    ExternalProject_Get_Property(EP_BeetreePlatformStm32g0xx BINARY_DIR)
    add_dependencies(EP_BeetreePlatformStm32g0xx EP_BeetreePlatform)

    __studiobee_add_library(Beetree::Platform::stm32g0xx STATIC ${BINARY_DIR} "beetree-platform-stm32g0xx")
    target_link_libraries(Beetree::Platform::stm32g0xx INTERFACE Beetree::Platform )
endif()

