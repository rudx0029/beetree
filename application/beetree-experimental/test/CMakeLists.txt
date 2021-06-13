find_package(GTest REQUIRED NO_PACKAGE_ROOT_PATH)

add_executable(test-beetree-experimental test-expected.cpp)

target_link_libraries(test-beetree-experimental PRIVATE GTest::gmock_main BeeTree::Experimental)

add_test(NAME test-beetree-experimental COMMAND test-beetree-experimental)
