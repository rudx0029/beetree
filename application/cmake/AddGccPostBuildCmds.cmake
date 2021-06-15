#[======================================================================[.rst:

^^^^^^^^^^^^^^^^^^^
AddGccPostBuildCmds
^^^^^^^^^^^^^^^^^^^

Adds the following GCC commands to a post build:

* objcopy (to create a binary from an elf)
* size (to print out the RAM/ROM usage of the executable)
* objdump (to view the object map of the executable)

#]======================================================================]
function(add_gcc_post_build_cmds target_name)

    if(EXISTS ${CMAKE_OBJCOPY})
        message(STATUS "${target_name} post build objcopy enabled")
        add_custom_command(
            TARGET ${target_name}
            POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${target_name}>
                    $<TARGET_FILE_DIR:${target_name}>/${target_name}.bin
            COMMAND ${CMAKE_COMMAND} -E echo "-- built: ${target_name}.bin"
        )

        get_filename_component(dir ${CMAKE_OBJCOPY} DIRECTORY)
        get_filename_component(fname ${CMAKE_OBJCOPY} NAME)

        string(REPLACE objcopy size fnameSizeBinUtil ${fname})
        find_program(
            BEETREE_SIZE_BINUTIL
            NAMES ${fnameSizeBinUtil}
            HINTS ${dir}
        )
    else()
        message(
            STATUS "objcopy bin util not found - skipping post build command for ${target_name}"
        )
    endif()

    if(BEETREE_SIZE_BINUTIL)
        message(STATUS "${target_name} post build size enabled")
        add_custom_command(
            TARGET ${target_name}
            POST_BUILD
            COMMAND ${BEETREE_SIZE_BINUTIL} -B $<TARGET_FILE:${target_name}>
        )
    else()
        message(STATUS "size bin util not found - skipping post build command for ${target_name}")
    endif()

    if(EXISTS ${CMAKE_OBJDUMP})
        message(STATUS "${target_name} post build objdump enabled")
        add_custom_command(
            TARGET ${target_name}
            POST_BUILD
            COMMAND ${CMAKE_OBJDUMP} -t $<TARGET_FILE:${target_name}> >
                    $<TARGET_FILE_DIR:${target_name}>/${target_name}.objdump.txt
        )
    else()
        message(
            STATUS "objdump bin util not found - skipping post build command for ${target_name}"
        )
    endif()
endfunction()
