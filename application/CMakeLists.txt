# CMake Module Path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

add_subdirectory(beetree)
add_subdirectory(beetree-start-pack)
add_subdirectory(beetree-experimental)

install(
    EXPORT Beetree
    FILE BeetreeConfig.cmake
    NAMESPACE Beetree::
    DESTINATION cmake
)