#[======================================================================[.rst:

Fetch nlohmann_json
~~~~~~~~~~~~~~~~~~~

Fetches nlohman_json single header library from the local filesystem (if
it exists) or downloads the content.

Targets
-------

``nlohmann_json::nlohmann_json``
    The header only json library. Include in source with 
    ``#include <nlohmann_json/json.hpp>``

Links
-----

* https://github.com/nlohmann/json
#]======================================================================]


set(_nljsonVersion v3.7.3)
set(_nljsonDir "${PROJECT_SOURCE_DIR}/thirdparty/nlohmann_json-${_nljsonVersion}")
set(_nljsonPath "${_nljsonDir}/include/nlohmann/json.hpp")

if(EXISTS "${_nljsonPath}")
    message(STATUS "[BeeTree] Sourcing nlohmann json from ${_nljsonDir}")
    
    # Configure the header only library
    add_library(nlohmann_json INTERFACE)
    add_library(nlohmann_json::nlohmann_json ALIAS nlohmann_json)
    target_include_directories(nlohmann_json INTERFACE ${_nljsonDir}/include)    
else()
    message(STATUS "[BeeTree] Sourcing nlohmann json from https://github.com/nlohmann/json/raw/${_nljsonVersion}")
    # Download the single header file for nlohmann json 
    file(DOWNLOAD    
        https://github.com/nlohmann/json/raw/${_nljsonVersion}/single_include/nlohmann/json.hpp
        ${CMAKE_BINARY_DIR}/_deps/nlohmann_json/include/nlohmann/json.hpp
    )   

    # Configure the header only library
    add_library(nlohmann_json INTERFACE)
    add_library(nlohmann_json::nlohmann_json ALIAS nlohmann_json)
    target_include_directories(nlohmann_json INTERFACE ${CMAKE_BINARY_DIR}/thirdparty/nlohmann/include)
endif()