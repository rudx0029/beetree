#[======================================================================[.rst:

Beetree Add Tokens
^^^^^^^^^^^^^^^^^^

Synopsis
--------
::
    beetree_add_tokens(target   TOKENS tokens.json ...
                                [HEADER <binary-dir>/include/<target>/tokens.hpp]
                                [MAP <binary-dir>/<target>-token-map.json]
                        )
#]======================================================================]

find_package(BeeTreeTools REQUIRED)
find_package(Python3 REQUIRED)

function(beetree_add_tokens target)

    get_target_property(binDir ${target} BINARY_DIR)

    cmake_parse_arguments(
        ""
        ""
        "HEADER;MAP"
        "TOKENS"
        ${ARGN}
    )

    if(NOT _HEADER)
        set(_HEADER ${binDir}/include/${target}/tokens.hpp)
        message(STATUS "beetree_add_tokens: using default token header path ${_HEADER}")

        target_include_directories(${target} PUBLIC ${binDir}/include)
        message(STATUS "beetree_add_tokens: added ${binDir}/include to the target's include path.")
    endif()

    if(NOT _MAP)
        set(_MAP ${binDir}/${target}-token-map.json)
        message(STATUS "beetree_add_tokens: using default token map path ${_MAP}")
    endif()

    if(NOT _TOKENS)
        message(FATAL_ERROR "Please provide one or more JSON token files")
    endif()

    add_custom_command(
        OUTPUT ${_HEADER} ${_MAP}
        COMMAND
            ${CMAKE_COMMAND} -E echo "Generating tokens for ${target}"
        COMMAND
            Python3::Interpreter ${BeeTreeTools_MAKE_TOKENS} ${_HEADER} ${_MAP} ${_TOKENS}
        DEPENDS ${_TOKENS}
    )

    add_custom_target(
        ${target}-tokens
        DEPENDS ${_HEADER} ${_MAP}
        SOURCES ${_HEADER} ${_MAP}
    )
    add_dependencies(${target} ${target}-tokens)
endfunction()
