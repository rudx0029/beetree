add_library(beetree-experimental INTERFACE)
add_library(BeeTree::Experimental ALIAS beetree-experimental)
target_include_directories(
    beetree-experimental
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)
target_link_libraries(beetree-experimental INTERFACE Beetree::Beetree)
set_target_properties(beetree-experimental PROPERTIES EXPORT_NAME Experimental)

# Tokens
# ------

set(tokensInc ${CMAKE_CURRENT_BINARY_DIR}/include)
set(tokensPath ${tokensInc}/beetree/experimental/tokens.hpp)
set(tokensMapPath ${CMAKE_CURRENT_BINARY_DIR}/beetree-experimental-token-map.json)


find_package(BeeTreeTools REQUIRED)


add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/experimental/tokens.hpp
            ${CMAKE_CURRENT_BINARY_DIR}/beetree-experimental-token-map.json
    COMMAND ${CMAKE_COMMAND} -E echo "Generating tokens for beetree-experimental"
    COMMAND
        python3 ${BeeTreeTools_MAKE_TOKENS}
        ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/experimental/tokens.hpp
        ${CMAKE_CURRENT_BINARY_DIR}/beetree-experimental-token-map.json
        ${CMAKE_CURRENT_SOURCE_DIR}/tokens.json
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tokens.json ${BeeTreeTools_MAKE_TOKENS}
)

add_custom_target(
    beetree-experimental-generated
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/experimental/tokens.hpp
    SOURCES ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/experimental/tokens.hpp
)
target_include_directories(beetree-experimental INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>)
add_dependencies(beetree-experimental beetree-experimental-generated)

# Test
# ----
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

# Install
# -------
include(GNUInstallDirs)
install(
    TARGETS beetree-experimental
    EXPORT Beetree
)
install(
    DIRECTORY include/ ${CMAKE_CURRENT_BINARY_DIR}/include/
    TYPE INCLUDE
)

# TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# Figure out why the install fails on installing ${CMAKE_CURRENT_BINARY_DIR}/include/

# install(
#     FILES ${tokensMapPaht}
#     DESTINATION ${CMAKE_INSTALL_DATADIR}/beetree
#     COMPONENT beetree-view
# )
