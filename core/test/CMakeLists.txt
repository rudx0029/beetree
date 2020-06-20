#[====================================[.rst:

Beetree Tests
=============

:test-beetree-units:
    test coverage of beetree/units

:test-beetree-engine:
    test coverage of beetree/engine
    
:test-beetree-btos:
    test coverage of beetree/btos
    
:test-beetree-registry:
    test coverage of beetree/registry
    
:test-beetree-nodes:
    test coverage of beetree/nodes

Dependencies
------------

- Beetree::TestAPI
- Beetree::Beetree

#]====================================]

#units
add_executable(test-beetree-units
    units/test-units.cpp
    units/test-units-trig.cpp
    units/test-units-methods.cpp
    units/test-units-fixed-pt.cpp
    units/test-units-rand.cpp
    units/fibonochi.hpp
)
target_link_libraries(test-beetree-units
    PRIVATE
        Beetree::TestAPI
        Beetree::Beetree
)
add_test(NAME test-beetree-units COMMAND test-beetree-units)

#engine test
add_executable(test-beetree-engine
    engine/test-stack.cpp
    engine/test-engine.cpp
    engine/test-engine-exceptions.cpp
    engine/test-try-catch.cpp
    engine/test-port.cpp
)
target_link_libraries(test-beetree-engine
    PRIVATE
        Beetree::TestAPI
        Beetree::Beetree
)
add_test(NAME test-beetree-engine COMMAND test-beetree-engine)

# btos tests
add_executable(test-beetree-btos
    btos/test-stack.cpp
)
target_link_libraries(test-beetree-btos
    PRIVATE
        Beetree::TestAPI
        Beetree::Beetree
)
add_test(NAME test-beetree-btos COMMAND test-beetree-btos)

# registry tests
add_executable(test-beetree-registry
    #registry/test-register-bank.cpp
    registry/test-register-trace.cpp
)
target_link_libraries(test-beetree-registry
    PRIVATE
        Beetree::TestAPI
        Beetree::Beetree
)
add_test(NAME test-beetree-registry COMMAND test-beetree-registry)

# nodes
add_executable(test-beetree-nodes
    nodes/test-repeat-until.cpp
    nodes/test-repeat-for.cpp
    nodes/test-inverter.cpp
    nodes/test-succeeder.cpp
    nodes/test-select-if.cpp
    nodes/test-sequence.cpp
    nodes/test-select.cpp
    nodes/test-action.cpp
)
target_link_libraries(test-beetree-nodes
    PRIVATE
        Beetree::TestAPI
        Beetree::Beetree
)
add_test(NAME test-beetree-nodes COMMAND test-beetree-nodes)
