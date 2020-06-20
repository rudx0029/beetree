//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <string>
#include <vector>
#include "beetree/test/gtest-ns.hpp"

namespace bte {
namespace test {
class ReqList
{
public:
    using list           = std::vector<std::string>;
    using const_iterator = list::const_iterator;

    const_iterator begin() const { return m_list.begin(); }
    const_iterator end() const { return m_list.end(); }

    ReqList& operator<<(std::string s);

private:
    list m_list;
};

/// A class for recording behavior style requirements embedded in the gtest
/// output
///
/// Usage:
/// @code
/// BehaviorReqs reqs; // in the test fixture
/// ...
/// // in the test
/// reqs.given << "the requirements";
/// reqs.when << "verifying";
/// reqs.then << "everything meets the requirements";
/// ...
/// // in the test fixture's TearDown overridden method
/// reqs.commit();
/// @endcode
///
class BehaviorReqTest : public gtest::Test
{
protected:
    ~BehaviorReqTest();
    static void Feature(std::string s);

    ReqList Scenario;  ///< the description of the behavior
    ReqList Given;     ///< a statement of the state of the scenario
    ReqList When;      ///< the action that invokes the behavior
    ReqList Then;      ///< the expected result of the behavior
};

}  // namespace test
}  // namespace bte