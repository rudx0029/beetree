#[======================================================================[.rst:

Beetree Add Registry
^^^^^^^^^^^^^^^^^^^^

Synopsis
--------
::
    beetree_install_registry(target [INCLUDE_PATH <binary-dir>/include/] 
                                    [INDEX <target>-registry-index.json]
                                    [INSTALL_DIR <install-data-dir>/<target>]
                                    [REGISTRY_DIR <source-dir>/registry]
                                )
#]======================================================================]

find_package(BeeTreeTools REQUIRED)
find_package(Python3 REQUIRED)

function(beetree_install_registry target)

    get_target_property(binDir ${target} BINARY_DIR)
    get_target_property(srcDir ${target} SOURCE_DIR)

    cmake_parse_arguments(
        "" "" "INCLUDE_PATH;INDEX;INSTALL_DIR;REGISTRY_DIR" "" ${ARGN}
    )

    if(NOT _INCLUDE_PATH)
        set(_INCLUDE_PATH ${binDir}/include/)
        message(STATUS "beetree_install_registry: using default include path ${_INCLUDE_PATH}.")
    endif()

    if(NOT _INDEX)
        set(_INDEX ${binDir}/${target}-registry-index.json)
        message(STATUS "beetree_install_registry: using default index ${_INDEX}.")
    endif()

    if(NOT _INSTALL_DIR)
        set(_INSTALL_DIR ${CMAKE_INSTALL_DATADIR}/${target})
        message(STATUS "beetree_install_registry: using default install dir ${_INSTALL_DIR}")
    endif()

    if(NOT _REGISTRY_DIR)
        set(_REGISTRY_DIR ${srcDir}/registry/)
        message(STATUS "beetree_install_registry: using default registry dir ${_REGISTRY_DIR}")
    endif()

    install(
        DIRECTORY ${_INCLUDE_PATH}
        TYPE INCLUDE
        COMPONENT ${target}-development
    )

    install(
        FILES ${_INDEX}
        DESTINATION ${_INSTALL_DIR}
        COMPONENT ${target}-view
    )

    install(
        DIRECTORY ${_REGISTRY_DIR}
        DESTINATION ${_INSTALL_DIR}
        COMPONENT ${target}-view
    )
endfunction()
