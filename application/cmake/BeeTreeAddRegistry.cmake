#[======================================================================[.rst:

Beetree Add Registry
^^^^^^^^^^^^^^^^^^^^

Synopsis
--------
::
    beetree_add_registry(target REGISTER_BANKS register-bank.json ... 
                                [INCLUDE_PATH <binary-dir>/include/<target>/registry]
                                [INDEX <target>-registry-index.json]
                                [NAMESPACE <target>]
                                [REGISTER_TYPE_PATH  ${INCLUDE_PATH}/register-bank-type.hpp]
                        )
#]======================================================================]

find_package(BeeTreeTools REQUIRED)
find_package(Python3 REQUIRED)

function(beetree_add_registry target)

    get_target_property(binDir ${target} BINARY_DIR)

    cmake_parse_arguments(
        "" "" "INCLUDE_PATH;INDEX;NAMESPACE;REGISTER_TYPE_PATH" "REGISTER_BANKS" ${ARGN}
    )

    if(NOT _NAMESPACE)
        set(_NAMESPACE ${target})
        message(STATUS "beetree_add_registry: using default namespace ${_NAMESPACE}.")
    endif()

    if(NOT _INCLUDE_PATH)
        set(_INCLUDE_PATH ${binDir}/include/${target}/registry)
        message(STATUS "beetree_add_registry: using default include path ${_INCLUDE_PATH}.")
        target_include_directories(${target} PUBLIC ${binDir}/include)
        message(STATUS "beetree_add_registry: added ${binDir}/include to the target's include path.")
    endif()

    if(NOT _INDEX)
        set(_INDEX ${binDir}/${target}-registry-index.json)
        message(STATUS "beetree_add_registry: using default index ${_INDEX}.")
    endif()

    if(NOT _REGISTER_TYPE_PATH)
        set(_REGISTER_TYPE_PATH ${_INCLUDE_PATH}/register-bank-type.hpp)
        message(
            STATUS
                "beetree_add_registry: using default path for the register bank type ${_REGISTER_TYPE_PATH}."
        )
    endif()

    if(NOT _REGISTER_BANKS)
        message(FATAL_ERROR "Please provide one or more JSON register bank files")
    endif()

    # generate the registry headers
    foreach(jsonBank ${_REGISTER_BANKS})
        get_filename_component(name ${jsonBank} NAME_WLE)
        list(APPEND registerBanks ${_INCLUDE_PATH}/${name}.hpp)
    endforeach()

    add_custom_command(
        OUTPUT ${_REGISTER_TYPE_PATH} ${registerBanks} ${_INDEX}
        COMMAND ${CMAKE_COMMAND} -E echo "Generating ${target} registry."
        COMMAND
            Python3::Interpreter ${BeeTreeTools_MAKE_REGISTRY} --namespace ${_NAMESPACE} --out_dir
            ${_INCLUDE_PATH} --index_path ${_INDEX} --registers ${_REGISTER_BANKS}
        DEPENDS ${_REGISTER_BANKS}
    )

    add_custom_target(
        ${target}-registry
        DEPENDS ${_REGISTER_TYPE_PATH} ${registerBanks} ${_INDEX}
        SOURCES ${_REGISTER_TYPE_PATH} ${registerBanks} ${_INDEX}
    )
    add_dependencies(${target} ${target}-registry)
endfunction()
