//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <array>
#include <memory>
#include <type_traits>
#include "beetree/experimental/expected.hpp"
#include "memory.h"

struct CopyOnly
{
    using array_type = std::array<int, 10>;

    CopyOnly()                = default;
    CopyOnly(const CopyOnly&) = default;
    CopyOnly(CopyOnly&&)      = delete;
    CopyOnly& operator=(const CopyOnly&) = default;
    CopyOnly& operator=(CopyOnly&&) = delete;

    const array_type& array() const { return m_values; }
    array_type&       array() { return m_values; }

private:
    array_type m_values;
};

struct MoveOnly
{
public:
    using array_type = CopyOnly::array_type;

    array_type& array() { return m_wrapper->array(); }

private:
    std::unique_ptr<CopyOnly> m_wrapper = std::make_unique<CopyOnly>();
};

TEST(Expected, copy_only_is_copy_only)
{
    static_assert(!std::is_move_constructible_v<CopyOnly>, "CopyOnly is move constructible");
    static_assert(!std::is_move_assignable_v<CopyOnly>, "CopyOnly is move assignable");
    static_assert(std::is_copy_constructible_v<CopyOnly>, "CopyOnly is not copy constructible");
    static_assert(std::is_copy_assignable_v<CopyOnly>, "CopyOnly is not copy assignable");
}

TEST(Expected, move_only_is_move_only)
{
    static_assert(std::is_move_constructible_v<MoveOnly>, "MoveOnly is not move constructible");
    static_assert(std::is_move_assignable_v<MoveOnly>, "MoveOnly is not move assignable");
    static_assert(!std::is_copy_constructible_v<MoveOnly>, "MoveOnly is copy constructible");
    static_assert(!std::is_copy_assignable_v<MoveOnly>, "MoveOnly is copy assignable");
}

using ::testing::ElementsAre;
using ::testing::ElementsAreArray;

TEST(Expected, copy_only_unexpected)
{
    using unexpected = bte::experimental::unexpected<CopyOnly>;

    {  // constructor
        CopyOnly expect;
        expect.array() = {3, 2, 1, 6, 5, 4, 9, 8, 7, 0};
        unexpected test(expect);
        EXPECT_THAT(test->array(), ElementsAreArray(expect.array()));
        EXPECT_THAT(test.value().array(), ElementsAreArray(expect.array()));
    }

    {  // copy constructor
        CopyOnly expect;
        expect.array() = {3, 2, 1, 6, 5, 4, 9, 8, 7, 0};

        unexpected orig(expect);
        unexpected test(orig);
        EXPECT_THAT(test->array(), ElementsAreArray(expect.array()));
        EXPECT_THAT(test.value().array(), ElementsAreArray(expect.array()));
    }

    {  // copy assignment
        CopyOnly expect;
        expect.array() = {3, 2, 1, 6, 5, 4, 9, 8, 7, 0};

        CopyOnly dummy;
        dummy.array() = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        unexpected copy(expect);
        unexpected test(dummy);

        test = copy;
        EXPECT_THAT(test->array(), ElementsAreArray(expect.array()));
        EXPECT_THAT(test.value().array(), ElementsAreArray(expect.array()));
    }
}

TEST(Expected, move_only_unexpected)
{

}

TEST(Expected, move_only_semantics_unexpected)
{

}

TEST(Expected, copy_only_move_only_test_structs)
{
    CopyOnly copy;
    MoveOnly move;

    int i = 0;
    for (auto iter = copy.array().begin(); copy.array().end() != iter; iter++)
    {
        *iter = i++;
    }

    auto miter = move.array().begin();
    auto citer = copy.array().begin();
    for (; copy.array().end() != citer && miter != move.array().end(); citer++, miter++)
    {
        *miter = *citer;
    }

    EXPECT_TRUE(0 == memcmp(move.array().data(),
                            copy.array().data(),
                            sizeof(CopyOnly::array_type::value_type) * copy.array().size()));
}