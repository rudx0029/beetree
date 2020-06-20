add_library(beetree-startpk-test-api INTERFACE)
add_library(Beetree::StartPack::TestAPI ALIAS beetree-startpk-test-api)
set_target_properties(beetree-startpk-test-api PROPERTIES EXPORT_NAME StartPack::TestAPI)


# Dependencies
# ------------
target_include_directories(
    beetree-startpk-test-api
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)

# Install
# -------
install(
    TARGETS beetree-startpk-test-api
    EXPORT Beetree
    PUBLIC_HEADER DESTINATION include COMPONENT Development
)
install(DIRECTORY include/ TYPE INCLUDE COMPONENT Development)
