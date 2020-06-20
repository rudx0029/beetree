//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test/behavior-reqs.hpp"
#include "beetree/test/gtest-ns.hpp"

namespace bte {
namespace test {
static void commit(const char* name, std::string s) { ::testing::Test::RecordProperty(name, s); }

/// concatenate the list into a semi-colon delimited string and commit
/// to the test record
static void commit(const char* name, const ReqList& reqs)
{
    std::string r;
    bool        first_time = true;
    for (const std::string& s : reqs)
    {
        if (first_time)
            r = s;
        else
            r.append("; ").append(s);

        first_time = false;
    }
    commit(name, std::move(r));
}

ReqList& ReqList::operator<<(std::string s)
{
    m_list.emplace_back(std::move(s));
    return *this;
}

void BehaviorReqTest::Feature(std::string s)
{
    std::cout << "\033[0;32m"
              << "[==========]"
              << "\033[0;0m" << std::endl;
    std::cout << "\033[0;32m"
              << "[ feature  ]\033[0;0m "
              << "\033[1m" << s << "\033[0m" << std::endl;
    std::cout << "\033[0;32m"
              << "[----------]"
              << "\033[0;0m" << std::endl;
    commit("feature", std::move(s));
}

/// commit the requirements to the test record
BehaviorReqTest::~BehaviorReqTest()
{
    commit("scenario", this->Scenario);
    commit("given", this->Given);
    commit("when", this->When);
    commit("then", this->Then);
}
}  // namespace test
}  // namespace bte