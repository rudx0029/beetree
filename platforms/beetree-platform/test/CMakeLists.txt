#[====================================[.rst:

Beetree Platform Tests
================================

:test-beetree-platform:
    test coverage of beetree/platform

#]====================================]

add_executable(test-beetree-platform test-array-ref.cpp)
target_link_libraries(test-beetree-platform PRIVATE Beetree::gmock_main Beetree::Platform  )
add_test(NAME test-beetree-platform COMMAND test-beetree-platform)
