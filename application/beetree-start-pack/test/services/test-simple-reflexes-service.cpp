//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/btos/flags.hpp"
#include "beetree/models/data/reflex.hpp"
#include "beetree/services/simple-reflexes-service.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/test-api/matchers/flag.hpp"

using namespace bte;
using gtest::NiceMock;
using test::FlagEquals;

class SimpleReflexesServiceTests : public test::BehaviorReqTest
{
protected:
    struct MockListener : public IReflexesService::Listener
    {
        MOCK_METHOD1(on_reflex_activated, void(Reflex));
        MOCK_METHOD0(on_all_reflexes_deactivated, void());
    };

    static void SetUpTestCase() { Feature("beetree-startpk-reflexes"); }
    void        SetUp() override { svc.configure_listener(mock_listener); }

    ReflexesModel          model;
    SimpleReflexesService  svc{model};
    NiceMock<MockListener> mock_listener;
};

TEST_F(SimpleReflexesServiceTests, reflex_activated_listeners_notified)
{
    Scenario << "A robot reflexes";

    Given << "a robot";
    When << "a reflex occurs";
    Then << "listeners are notified";

    Reflex expected_reflex = Reflex::make<31>();

    EXPECT_CALL(mock_listener, on_reflex_activated(FlagEquals(expected_reflex))).Times(1);

    svc.activate_reflex(expected_reflex);
}

TEST_F(SimpleReflexesServiceTests, reflexes_deactivated_listeners_notified)
{
    Scenario << "All reflexes end";
    Given << "A robot with an active reflex";
    When << "all reflexes end";
    Then << "listeners are notified";

    EXPECT_CALL(mock_listener, on_all_reflexes_deactivated()).Times(0);
    svc.deactivate_all_reflexes();

    Given << "A robot with no active reflexes";
    When << "all reflexes end";
    Then << "listeners are not notified";

    EXPECT_CALL(mock_listener, on_all_reflexes_deactivated()).Times(1);
    svc.activate_reflex(Reflex::make<1>());
    svc.deactivate_all_reflexes();
}

TEST_F(SimpleReflexesServiceTests, reflex_activated_model_updated)
{
    Scenario << "A robot reflexes";

    Given << "A robot";
    When << "one or more reflexes happen";
    Then << "then the model is updated with the current reflexes";

    Reflex first_reflex  = Reflex::make<10>();
    Reflex second_reflex = Reflex::make<1>();

    svc.deactivate_all_reflexes();

    svc.activate_reflex(first_reflex);
    EXPECT_TRUE(flags::any(svc.model().current_reflexes));

    svc.activate_reflex(second_reflex);
    EXPECT_TRUE(flags::any(svc.model().current_reflexes));
    EXPECT_EQ(svc.model().current_reflexes.bitmask, first_reflex.value | second_reflex.value);
}

TEST_F(SimpleReflexesServiceTests, reflexes_deactivated_model_updated)
{
    Scenario << "All reflexes end";
    Given << "A robot with an active reflex";
    When << "all reflexes end";
    Then << "the model is updated with no current reflexes";

    svc.activate_reflex(Reflex::make<0>());

    svc.deactivate_all_reflexes();
    EXPECT_FALSE(flags::any(svc.model().current_reflexes));
    EXPECT_EQ(svc.model().current_reflexes.bitmask, 0);
}
