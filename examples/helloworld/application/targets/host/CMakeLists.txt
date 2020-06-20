#[======================================================================[.rst:
#
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
# Hello World! for the console
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#
# The hello world executable for the console.
#
# Details
# -------
#
# We add the executable to create a deployable application for the specific
# platform. In this case, for your host system. The sources for the
# executable are minimal, only ``main.cpp``. This is because the core of the
# application is linked to the ``Helloworld::Helloworld`` platform agnostic
# library, while linking to ``Helloworld::Platform::Host`` gives the
# details on how to run on the stm32f030x8 platform.  Finally, we add any
# compile or linking options required by the platform here.
#
#]======================================================================]
add_executable(helloworld-app-host main.cpp)

target_link_libraries(helloworld-app-host PRIVATE Helloworld::Helloworld Helloworld::Platform::Host)

install(TARGETS helloworld-app-host COMPONENT helloworld-runtime)
