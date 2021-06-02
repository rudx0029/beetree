#[====================================[.rst:

Beetree Platform Tests
================================

:test-beetree-platform:
    test coverage of beetree/platform

#]====================================]

find_package(GTest REQUIRED NO_PACKAGE_ROOT_PATH)

add_executable(test-beetree-platform test-array-ref.cpp)
target_link_libraries(test-beetree-platform PRIVATE Beetree::Platform GTest::gmock_main)
add_test(NAME test-beetree-platform COMMAND test-beetree-platform)
