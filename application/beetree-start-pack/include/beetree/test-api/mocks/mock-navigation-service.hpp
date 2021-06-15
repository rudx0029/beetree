#include "beetree/services/i-navigation-service.hpp"
#include "beetree/test-api/gtest-ns.hpp"

namespace bte {
namespace test {

class MockNavigationService : public bte::INavigationService
{
public:
    bte::NavigationModel fake_model;

    MOCK_CONST_METHOD0(model, const NavigationModel&());
    MOCK_METHOD2(go_to, bte::Task(const units::Coordinate&, bte::Clock::ms));
    MOCK_METHOD2(rotate_to, bte::Task(units::Angle, bte::Clock::ms));
    MOCK_METHOD0(null_odometry, void());

    MockNavigationService()
    {
        ON_CALL(*this, model()).WillByDefault(testing::ReturnRef(fake_model));
    }
};
}  // namespace test
}  // namespace bte