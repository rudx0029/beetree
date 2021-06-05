cmake_minimum_required(VERSION 3.14)
# Beetree Starter Pack Library
# ======================================
#
# Add-on library for Beetree::Beetree package with starter behaviors, reflexes, and services.
#
# ```
# Target Name    beetree-start-pack
# Package Name   Beetree::StartPack
# ```
#
# Behavior Nodes
# --------------
# - Go To
# - Move
# - Rotate
# - Stop
#
# Reflex Nodes
# --------------
# - bump-reflex
#
# Utility Nodes
# -------------
# - Hello World!
# - Wait For Reflexes
# - Activate/Deactivate Reflex
#     - Runs/Stops a Reflex
# - Enable/Disable All Reflexes
#     - Allows reflexes to be activated or blocks activation for all reflexes
# - Null Odometry
#     - Resets odometry
#
# Services
# --------
# - Bump
# - Debug
# - Motion
# - Navigation
# - Reflexes
#
# Facilities
# ----------
# - Differential Wheel Control
# - Differential Motion Sensing
#
add_library(beetree-start-pack STATIC)
add_library(Beetree::StartPack ALIAS beetree-start-pack)
set_target_properties(beetree-start-pack PROPERTIES EXPORT_NAME StartPack)

# Controllers
# -----------
target_sources(
    beetree-start-pack PRIVATE src/controllers/pid.cpp src/controllers/goal-controller.cpp
)

# Facilities
# ----------
target_sources(
    beetree-start-pack
    PRIVATE src/facilities/filters/motor-control-filter-zero.cpp
            src/facilities/filters/wheels-control-filter.cpp
            src/facilities/filters/encoder-filter.cpp
            src/facilities/filters/user-event-filter.cpp
            src/facilities/filters/wheel-motion-with-encoders-filter.cpp
            src/facilities/filters/wheel-motion-filter.cpp
            src/facilities/filters/differential-control-filter.cpp
            src/facilities/filters/simple-bump-filter.cpp
)

# Services
# --------
target_sources(
    beetree-start-pack
    PRIVATE src/services/simple-navigation-service.cpp
            src/services/simple-motion-service.cpp
            src/services/simple-reflexes-service.cpp
            src/services/simple-bump-service.cpp
            src/services/tasks/simple-go-to-position-task.cpp
            src/services/tasks/simple-rotate-task.cpp
            src/services/api/bump-api.cpp
            src/services/api/reflexes-api.cpp
)

# Nodes
# -----
target_sources(
    beetree-start-pack
    PRIVATE src/nodes/helloworld.cpp
            src/nodes/toggle-debug-led.cpp
            src/nodes/behaviors/go-to.cpp
            src/nodes/behaviors/move.cpp
            src/nodes/behaviors/null-odometry.cpp
            src/nodes/behaviors/rotate.cpp
            src/nodes/behaviors/stop.cpp
            src/nodes/behaviors/wait-for-reflexes.cpp
)

# Dependencies
# ------------
target_link_libraries(beetree-start-pack PRIVATE Beetree::Beetree)
target_include_directories(
    beetree-start-pack PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                              $<INSTALL_INTERFACE:include>
)

# Tokens
# ------

find_package(BeeTreeTools REQUIRED)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/startpk/tokens.hpp
           ${CMAKE_CURRENT_BINARY_DIR}/beetree-start-pack-token-map.json
    COMMAND ${CMAKE_COMMAND} -E echo "Generating tokens for beetree-startpk"
    COMMAND
        python3 ${BeeTreeTools_MAKE_TOKENS}
        ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/startpk/tokens.hpp
        ${CMAKE_CURRENT_BINARY_DIR}/beetree-start-pack-token-map.json
        ${CMAKE_CURRENT_SOURCE_DIR}/tokens.json
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tokens.json ${BeeTreeTools_MAKE_TOKENS}
)

add_custom_target(
    beetree-startpk-generated
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/startpk/tokens.hpp
    SOURCES ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/startpk/tokens.hpp
)
target_include_directories(
    beetree-start-pack PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)
add_dependencies(beetree-start-pack beetree-startpk-generated)

# Test
# ----
if(BUILD_TESTING)
    add_library(beetree-startpk-test-api INTERFACE)
    add_library(Beetree::StartPack::TestAPI ALIAS beetree-startpk-test-api)
    set_target_properties(beetree-startpk-test-api PROPERTIES EXPORT_NAME StartPack::TestAPI)

    # Dependencies
    # ------------
    target_include_directories(
        beetree-startpk-test-api INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                           $<INSTALL_INTERFACE:include>
    )

    # Install
    # -------
    install(TARGETS beetree-startpk-test-api EXPORT Beetree)

    add_subdirectory(test)
endif()

# Install
# -------
install(
    TARGETS beetree-start-pack
    EXPORT Beetree
)
install(
    DIRECTORY include/ ${CMAKE_CURRENT_BINARY_DIR}/include/
    TYPE INCLUDE
)
# install(
#     FILES ${CMAKE_CURRENT_BINARY_DIR}/beetree-start-pack-token-map.json
#     DESTINATION "share/beetree"
#     COMPONENT View
# )
