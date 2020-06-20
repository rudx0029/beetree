#[======================================================================[.rst:
^^^^^^^^^^^^^^^^^^
Find BeeTree Tools
^^^^^^^^^^^^^^^^^^

Finds several tools used in building and developing a BeeTree application.

Python Scripts
--------------

``BeeTreeTools_MAKE_TOKENS``
    Full path to ``make-tokens.py`` to generate token information per 
    application

``BeeTreeTools_MAKE_REGISTRY``
    Full path to ``make-registry.py`` to generate registry information per
    application

#]======================================================================]

include(FindPackageHandleStandardArgs)

find_file(BeeTreeTools_MAKE_REGISTRY NAMES make-registry.py PATHS "${CMAKE_CURRENT_LIST_DIR}/../tools" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
find_file(BeeTreeTools_MAKE_TOKENS NAMES make-tokens.py PATHS "${CMAKE_CURRENT_LIST_DIR}/../tools" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)

find_package_handle_standard_args(BeeTreeTools
  REQUIRED_VARS
    BeeTreeTools_MAKE_REGISTRY
    BeeTreeTools_MAKE_TOKENS
)
