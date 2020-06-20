//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/core/tokens.hpp"
#include "beetree/registry/register-trace.hpp"
#include "beetree/test/behavior-reqs.hpp"
#include "beetree/test/gtest-ns.hpp"
#include "beetree/test/matchers/trace-package.hpp"

using namespace bte;

class RegisterTraceTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("beetree-registry"); }

    enum class TestItems
    {
        Item0,
        Item1,
        Item2,
        Item3,
        NUM_ITEMS
    };

    enum class TestBanks
    {
        Bank0,
        Bank1,
        Bank2,
        NUM_BANKS
    };

    class MockListener : public TraceListener
    {
    public:
        MOCK_METHOD2(on_log_received, void(TraceProcessor processor, const TracePackage& package));
    };

    AllocatedRegisterBank<TestItems>     bank0;
    AllocatedRegisterBank<TestItems>     bank1;
    AllocatedRegisterBank<TestItems>     bank2;
    AllocatedRegisterProvider<TestBanks> provider;
    TraceVerbosity                       verbosity{TraceVerbosity::Debug};
    TraceProcessor                       processor{TraceProcessor::ID_3};
    RegisterTrace                        trace;
    TraceManager                         trace_mgr;
    MockListener                         trace_listener;
    uint32_t                             seed = 345;

    void SetUp() override
    {
        trace_mgr.set_listener(&trace_listener);
        trace_mgr.set_verbosity(verbosity);
        trace_mgr.set_processor(processor);
        bte::set_trace_manager(&trace_mgr);

        // pre load each value
        uint32_t value     = seed;
        int      item0     = static_cast<int>(TestItems::Item0);
        int      num_items = static_cast<int>(TestItems::NUM_ITEMS);

        for (int i = item0; i < num_items; ++i)
        {
            bank0[static_cast<TestItems>(i)] = value++;
        }
        for (int i = item0; i < num_items; ++i)
        {
            bank1[static_cast<TestItems>(i)] = value++;
        }
        for (int i = item0; i < num_items; ++i)
        {
            bank2[static_cast<TestItems>(i)] = value++;
        }

        provider[TestBanks::Bank0] = bank0;
        provider[TestBanks::Bank1] = bank1;
        provider[TestBanks::Bank2] = bank2;

        trace.install(provider);
    }
};

TEST_F(RegisterTraceTests, tick)
{
    Given << "a beetree application with a registry trace referencing several registers";
    When << "the registery trace ticks";
    Then << "each registry item in each register bank is recorded as a debug trace";

    int      num_items = static_cast<int>(TestItems::NUM_ITEMS);
    int      num_banks = static_cast<int>(TestBanks::NUM_BANKS);
    uint32_t value     = seed;

    for (int bank_idx = 0; bank_idx < num_banks; ++bank_idx)
    {
        for (int item_idx = 0; item_idx < num_items; ++item_idx)
        {
            TracePackage expected;
            expected.token     = tokens::RegistryItem;
            expected.verbosity = verbosity;
            expected.channel   = bte::TraceChannel::Registry;
            expected.num_args  = 3;
            expected.args[0]   = bank_idx;
            expected.args[1]   = item_idx;
            expected.args[2]   = value++;

            EXPECT_CALL(trace_listener,
                        on_log_received(processor, test::TracePackageEquals(expected)))
                .RetiresOnSaturation();

            trace.tick();
        }
    }
}