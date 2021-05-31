add_executable(test-beetree-experimental test-expected.cpp)

target_link_libraries(test-beetree-experimental PRIVATE gmock_main BeeTree::Experimental)

add_test(NAME test-beetree-experimental COMMAND test-beetree-experimental)
