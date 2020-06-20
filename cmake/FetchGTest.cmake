#[======================================================================[.rst:

Fetch GTest
^^^^^^^^^^^

Fetches the google test from https://github.com/google/googletest

Imported Packages
-----------------

* ``gtest``
* ``gmock``
* ``gtest_main``
* ``gmock_main``

#]======================================================================]

cmake_minimum_required(VERSION 3.14)

set(gtestTag release-1.10.0)
set(gtestArchive "${PROJECT_SOURCE_DIR}/thirdparty/googletest-${gtestTag}.tar.gz")
set(gtestRepo "https://github.com/google/googletest.git")

# On Windows MinGW systems, we need to turn pthreads off for gtest
if(WIN32)
    message(STATUS "[BeeTree] Disabling pthreads for gtest on Win32")
    set(gtest_disable_pthreads "ON")
endif()

include(FetchContent)

if(EXISTS ${gtestArchive})
    message(STATUS "[BeeTree] Sourcing google test from ${gtestArchive}")
    FetchContent_Declare(
        googletest
        URL ${gtestArchive}
    )
    FetchContent_MakeAvailable(googletest)    
else()
    message(STATUS "[BeeTree] Sourcing google test from ${gtestRepo}")
    # Download and unpack googletest at configure time
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY ${gtestRepo}
        GIT_TAG ${gtestTag}
    )
    FetchContent_MakeAvailable(googletest)
endif()
 