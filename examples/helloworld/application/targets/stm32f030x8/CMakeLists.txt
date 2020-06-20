#[======================================================================[.rst:
#
# ^^^^^^^^^^^^^^^^^^^^^^^^
# Hello World! Stm32f030x8
# ^^^^^^^^^^^^^^^^^^^^^^^^
#
# The hello world executable for the stm32f030x8 platform.
#
# Details
# -------
#
# We add the executable to create a deployable application for the specific
# platform. In this case, for the stm32f030x8 platform. The sources for the
# executable are minimal, only ``main.cpp``. This is because the core of the
# application is linked to the ``Helloworld::Helloworld`` platform agnostic
# library while linking to ``Helloworld::Platform::Stm32f030x8`` gives the
# details on how to run on the stm32f030x8 platform.  Finally, we add any
# compile or linking options required by the platform here.
#
# Link Script
# -----------
#
# Hello world for the Stm32f030x8 requires the link script at
# `platforms/helloworld-platform/share/STM32F030R8Tx_FLASH.ld`
#
#]======================================================================]
add_executable(helloworld-app-stm32f030x8 main.cpp)

target_link_libraries(
    helloworld-app-stm32f030x8
    PRIVATE Helloworld::Helloworld Helloworld::Platform::Stm32f030x8
)

# The platform will add the linker script *.ld to its interfer link options
target_link_options(
    helloworld-app-stm32f030x8
    PUBLIC $<TARGET_PROPERTY:Helloworld::Platform::Stm32f030x8,INTERFACE_LINK_OPTIONS>
)

set_target_properties(
    helloworld-app-stm32f030x8
    PROPERTIES OUTPUT_NAME "helloworld-app-stm32f030x8.elf"
)

include(AddGccPostBuildCmds)
add_gcc_post_build_cmds(helloworld-app-stm32f030x8)

install(TARGETS helloworld-app-stm32f030x8 COMPONENT helloworld-app-runtime)
