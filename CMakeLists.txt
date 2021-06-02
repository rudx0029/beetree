cmake_minimum_required(VERSION 3.15)
project(beetree-superbuild C CXX ASM)

option(STUDIOBEE_BUILD_TESTING "Enable configuring and building of Studio Bee unit tests" ON)
option(STUDIOBEE_QUIET_BUILD "Disable build logging of Studio Bee targets" OFF)

include(ExternalProject)

set(__studiobee_prefix ${CMAKE_CURRENT_BINARY_DIR}/studio-bee)
set(__studiobee_build ${__studiobee_prefix}/build)
if(STUDIOBEE_QUIET_BUILD)
    set(__studiobee_log_build FALSE)
else()
    set(__studiobee_log_build TRUE)
endif()

if(STUDIOBEE_BUILD_TESTING)
    ExternalProject_Add(
        EP_GoogleTest
        PREFIX ${__studiobee_prefix}/googletest
        URL "${CMAKE_CURRENT_SOURCE_DIR}/application/thirdparty/googletest-release-1.10.0.tar.gz"
        BINARY_DIR ${__studiobee_build}/googletest
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${__studiobee_prefix}/googletest
        LOG_BUILD ${__studiobee_log_build}
        LOG_OUTPUT_ON_FAILURE TRUE
        LOG_MERGED_STDOUTERR TRUE  
    )
endif()

ExternalProject_Add(
    EP_BeetreePlatform
    PREFIX ${__studiobee_prefix}/beetree-platform
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/platform
    BINARY_DIR ${__studiobee_build}/beetree-platform
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    CMAKE_CACHE_ARGS
        -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX:STRING=${__studiobee_prefix}/beetree-platform
        -DBEETREE_BUILD_TESTING:BOOL=${STUDIOBEE_BUILD_TESTING}
        -DGTest_DIR:STRING=${__studiobee_prefix}/googletest/lib/cmake/GTest
    LOG_BUILD ${__studiobee_log_build}
    LOG_OUTPUT_ON_FAILURE TRUE
    LOG_MERGED_STDOUTERR TRUE  
)
add_dependencies(EP_BeetreePlatform EP_GoogleTest)

ExternalProject_Add(
    EP_Beetree
    PREFIX ${__studiobee_prefix}/beetree
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/application
    BINARY_DIR ${__studiobee_build}/beetree
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    CMAKE_CACHE_ARGS
        -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX:STRING=${__studiobee_prefix}/beetree
        -DBEETREE_BUILD_TESTING:BOOL=${STUDIOBEE_BUILD_TESTING}
        -DBeetreePlatform_DIR:STRING=${__studiobee_prefix}/beetree-platform/cmake
        -DGTest_DIR:STRING=${__studiobee_prefix}/googletest/lib/cmake/GTest
    LOG_BUILD ${__studiobee_log_build}
    LOG_OUTPUT_ON_FAILURE TRUE
    LOG_MERGED_STDOUTERR TRUE  
)
add_dependencies(EP_Beetree EP_BeetreePlatform EP_GoogleTest)

add_library(Beetree::Beetree STATIC IMPORTED)
set_target_properties(
    Beetree::Beetree
    PROPERTIES IMPORTED_LOCATION ${__studiobee_prefix}/beetree/libbeetree.a
               INTERFACE_INCLUDE_DIRECTORIES ${__studiobee_prefix}/beetree/include
    LOG_BUILD TRUE
)
add_dependencies(Beetree::Beetree EP_Beetree)

add_library(Beetree::StartPack STATIC IMPORTED)
set_target_properties(
    Beetree::StartPack
    PROPERTIES IMPORTED_LOCATION ${__studiobee_prefix}/beetree/libbeetree-start-pack.a
               INTERFACE_INCLUDE_DIRECTORIES ${__studiobee_prefix}/beetree/include
)
add_dependencies(Beetree::StartPack Beetree::Beetree)

add_library(Beetree::TestAPI STATIC IMPORTED)
set_target_properties(
    Beetree::TestAPI
    PROPERTIES IMPORTED_LOCATION ${__studiobee_prefix}/beetree/libbeetree-test-api.a
               INTERFACE_INCLUDE_DIRECTORIES ${__studiobee_prefix}/beetree/include
)
add_dependencies(Beetree::TestAPI Beetree::Beetree)
