include(ExternalProject)

# Add gtest
set(__prefix ${CMAKE_BINARY_DIR}/thirdparty/googletest)
ExternalProject_Add(
    beetree-googletest
    PREFIX ${__prefix}    
    URL "${CMAKE_CURRENT_LIST_DIR}/../thirdparty/googletest-release-1.10.0.tar.gz"
    #URL_MD5 97c8d0b4e29aa4c663362b79ac2abc93 
    SOURCE_DIR ${__prefix}/source
    BINARY_DIR ${__prefix}/build
    INSTALL_DIR ${__prefix}/install
    BUILD_BYPRODUCTS    ${__prefix}/install/lib/libgtest.a
                        ${__prefix}/install/lib/libgtest_main.a
                        ${__prefix}/install/lib/libgmock.a
                        ${__prefix}/install/lib/libgmock_main.a
                        ${__prefix}/install/googletest/include
                        ${__prefix}/install/googlemock/include
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:STRING=${__prefix}/install
    )

# create the include directory so CMake doesn't complain
ExternalProject_Get_Property(beetree-googletest install_dir) 
file(MAKE_DIRECTORY ${install_dir}/include)

# gtest requires threads
find_package(Threads)

# add gtest libraries in Beetree namespace
add_library(Beetree::gtest UNKNOWN IMPORTED)
target_link_libraries(Beetree::gtest INTERFACE Beetree::gtest Threads::Threads)
set_target_properties(Beetree::gtest PROPERTIES 
    IMPORTED_LOCATION ${install_dir}/lib/libgtest.a 
    INTERFACE_INCLUDE_DIRECTORIES ${install_dir}/include
    )
add_dependencies(Beetree::gtest beetree-googletest)

add_library(Beetree::gtest_main UNKNOWN IMPORTED)
target_link_libraries(Beetree::gtest_main INTERFACE Beetree::gtest)
set_property(TARGET Beetree::gtest_main PROPERTY
    IMPORTED_LOCATION ${install_dir}/lib/libgtest_main.a 
    )
add_dependencies(Beetree::gtest_main beetree-googletest)

add_library(Beetree::gmock UNKNOWN IMPORTED)
target_link_libraries(Beetree::gmock INTERFACE Beetree::gtest)
set_property(TARGET Beetree::gmock PROPERTY
    IMPORTED_LOCATION ${install_dir}/lib/libgmock.a 
    )
add_dependencies(Beetree::gmock beetree-googletest)

add_library(Beetree::gmock_main UNKNOWN IMPORTED)
target_link_libraries(Beetree::gmock_main INTERFACE Beetree::gmock)
set_target_properties(Beetree::gmock_main PROPERTIES
    IMPORTED_LOCATION ${install_dir}/lib/libgmock_main.a 
    )
add_dependencies(Beetree::gmock_main beetree-googletest)
