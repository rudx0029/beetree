cmake_minimum_required(VERSION 3.14)
# Beetree Test API LIbrary
# ======================================
#
# Unit test convenience API for Beetree Applications
#
# ```
# Target Name    beetree-test-api
# Package Name   Beetree::TestAPI
# Exports        Google Test
# ```
add_library(beetree-test-api STATIC)
add_library(Beetree::TestAPI ALIAS beetree-test-api)
set_target_properties(beetree-test-api PROPERTIES EXPORT_NAME TestAPI)

target_sources(
    beetree-test-api
    PRIVATE
        src/mocks/mock-node.cpp
        src/mocks/platform-mock.cpp
        src/fakes/test-node.cpp
        src/behavior-reqs.cpp
        src/matchers/internal/coordinate-equals-matcher.cpp
        src/matchers/internal/pose-equals-matcher.cpp
        src/matchers/internal/node-matchers.cpp
        src/matchers/internal/motion-profile-equals-matcher.cpp
        src/matchers/internal/time-equals-matcher.cpp
        src/matchers/internal/trace-package-equals-matcher.cpp
        src/matchers/coordinate.cpp
        src/matchers/pose.cpp
        src/matchers/node.cpp
        src/matchers/motion-profile.cpp
        src/matchers/time.cpp
        src/matchers/trace-package.cpp
        src/trees/expect-tree.cpp
)

# Dependencies
# ------------
target_link_libraries(beetree-test-api PUBLIC gmock_main)
target_link_libraries(beetree-test-api PRIVATE Beetree::Beetree)
target_include_directories(
    beetree-test-api
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)
# Install
# -------

install(
    TARGETS
        beetree-test-api
        gtest
        gmock
        gmock_main
        COMPONENT
        Development
    EXPORT Beetree
)
install(DIRECTORY include/ TYPE INCLUDE COMPONENT Development)
