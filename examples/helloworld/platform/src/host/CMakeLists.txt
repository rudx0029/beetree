#[======================================================================[.rst:

^^^^^^^^^^^^
Hello World!
^^^^^^^^^^^^

Hello World! platform for the host's system

Depndencies
-----------

* Helloworld::Platform::Interface
* PlatformLibrary::Host

Result Package
--------------

``Helloworld::Platform::Stm32f030x8``
    Hello world! platform package for the stm32f030x8

``helloworld-plt-stm32f030x8``
    Hello world! platform library for the stm32f030x8

#]======================================================================]

add_library(helloworld-plt-host STATIC)
add_library(Helloworld::Platform::Host ALIAS helloworld-plt-host)

# Third Party
# -----------
include(FetchNLohmannJSON)

# Sources
# -------
target_sources(helloworld-plt-host PRIVATE internal-platform.hpp internal-platform.cpp)

# Dependencies
# ------------
target_link_libraries(
    helloworld-plt-host
    PUBLIC Helloworld::Platform::Interface
    PRIVATE PlatformLibrary::Host
    PRIVATE nlohmann_json::nlohmann_json
)

# Install
# -------
install(TARGETS helloworld-plt-host COMPONENT helloworld-development)
