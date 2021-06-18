add_executable(test-beetree-experimental test-expected.cpp)

target_link_libraries(test-beetree-experimental PRIVATE Beetree::gmock_main Beetree::Experimental)

add_test(NAME test-beetree-experimental COMMAND test-beetree-experimental)
