add_executable(test-beetree-startpk 
    # controller tests
    controllers/test-pid-controller.cpp
    controllers/test-goal-controller.cpp
    # facilities tests
    facilities/test-motor-control.cpp
    facilities/test-motor-encoder.cpp
    facilities/test-wheel-motion-filter.cpp        
    #services tests
    services/test-simple-motion-service.cpp
    services/test-simple-navigation-service.cpp
    services/test-simple-reflexes-service.cpp
    services/test-simple-bump-service.cpp
    services/fakes/fake-motion-service.cpp
)

target_link_libraries(test-beetree-startpk PRIVATE
    Beetree::StartPack
    Beetree::Beetree
    Beetree::TestAPI
)

add_test(NAME test-beetree-startpk COMMAND test-beetree-startpk)