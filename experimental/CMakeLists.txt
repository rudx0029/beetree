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
    OUTPUT ${tokensPath}
           ${tokensMapPath}
    COMMAND ${CMAKE_COMMAND} -E echo "Generating tokens for beetree-experimental"
    COMMAND
        python3 ${BeeTreeTools_MAKE_TOKENS}
        ${tokensPath}
        ${tokensMapPath}
        ${CMAKE_CURRENT_SOURCE_DIR}/tokens.json
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tokens.json ${BeeTreeTools_MAKE_TOKENS}
)

add_custom_target(
    beetree-experimental-generated
    DEPENDS ${tokensPath}
    SOURCES ${tokensPath}
)
target_include_directories(beetree-experimental INTERFACE $<BUILD_INTERFACE:${tokensInc}>)
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
    COMPONENT Development
    EXPORT Beetree
)
install(
    DIRECTORY include/ ${tokensInc}/
    TYPE INCLUDE
    COMPONENT Development
)
install(
    FILES ${tokensMapPaht}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/beetree
    COMPONENT beetree-view
)
