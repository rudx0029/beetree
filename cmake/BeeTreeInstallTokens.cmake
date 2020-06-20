#[======================================================================[.rst:

Beetree Install Tokens
^^^^^^^^^^^^^^^^^^^^^^

Synopsis
--------
::
    beetree_install_tokens(target   [INCLUDE_PATH <binary-dir>/include/] 
                                    [MAP <target>-token-map.json]
                                    [INSTALL_DIR <install-data-dir>/<target>]
                                )
#]======================================================================]

include(GNUInstallDirs)

function(beetree_install_tokens target)

    get_target_property(binDir ${target} BINARY_DIR)

    cmake_parse_arguments("" "" "INCLUDE_PATH;MAP;INSTALL_DIR;" "" ${ARGN})

    if(NOT _INCLUDE_PATH)
        set(_INCLUDE_PATH ${binDir}/include/)
        message(STATUS "beetree_install_tokens: using default include path ${_INCLUDE_PATH}.")
    endif()

    if(NOT _MAP)
        set(_MAP ${binDir}/${target}-token-map.json)
        message(STATUS "beetree_install_tokens: using default token map path ${_MAP}")
    endif()

    if(NOT _INSTALL_DIR)
        set(_INSTALL_DIR ${CMAKE_INSTALL_DATADIR}/${target})
        message(STATUS "beetree_install_tokens: using default install dir ${_INSTALL_DIR}")
    endif()

    # directories
    #  - binary include directory (both tokens and registry)
    #  - json register banks SOURCE_DIR/registry
    # files
    #   token-map.json
    #   registry-index.json

    install(
        DIRECTORY ${_INCLUDE_PATH}
        TYPE INCLUDE
        COMPONENT ${target}-development
    )
    install(
        FILES ${_MAP}
        DESTINATION ${_INSTALL_DIR}
        COMPONENT ${target}-view
    )
endfunction()
