#[======================================================================[.rst:

^^^^^^^^^^^^
Hello World!
^^^^^^^^^^^^

Hello World! platform interface. A header only library to interface the
application with the specific platform

Result Package
--------------

``Helloworld::Platform::Interface``
    Hello world! platform interface package (header only library)

#]======================================================================]
add_library(helloworld-plt-interface INTERFACE)
add_library(Helloworld::Platform::Interface ALIAS helloworld-plt-interface)

target_sources(
    helloworld-plt-interface
    INTERFACE include/helloworld-platform/helloworld-platform.hpp
)
target_include_directories(
    helloworld-plt-interface
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)

# Add targets based on platform/architecture
if(CMAKE_SYSTEM_PROCESSOR STREQUAL CMAKE_HOST_SYSTEM_PROCESSOR)
    add_subdirectory(src/host)
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "cortex-m0")
    add_subdirectory(src/stm32f030x8)
endif()

install(DIRECTORY include/ TYPE INCLUDE COMPONENT helloworld-development)
