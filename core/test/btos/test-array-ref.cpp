//------------------------------------------------------------------------------
// Copyright (C) 2021 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

///
/// @file Contains unit tests for the bte::array_ref<T> array reference wrapper
///

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "beetree/btos/array-ref.hpp"

static constexpr std::size_t N{8};
static int fib_arr[N] = {1, 1, 2, 3, 5, 8, 13, 21};
static std::array<int, N> fib_stdarr = {1, 1, 2, 3, 5, 8, 13, 21};

TEST(array_ref, ptr_constructor)
{
    auto aref_under_test = bte::array_ref(fib_arr, N);

    EXPECT_THAT(aref_under_test, ::testing::ElementsAreArray(fib_arr));
    EXPECT_EQ(aref_under_test.data(), fib_arr);
}

TEST(array_ref, ref_constructor)
{
    auto aref_under_test = bte::array_ref(fib_arr);

    EXPECT_THAT(aref_under_test, ::testing::ElementsAreArray(fib_arr));
    EXPECT_EQ(aref_under_test.data(), fib_arr);
}

TEST(array_ref, arr_constructor)
{
    auto aref_under_test = bte::array_ref(fib_stdarr);

    EXPECT_THAT(aref_under_test, ::testing::ElementsAreArray(fib_stdarr));
    EXPECT_EQ(aref_under_test.data(), fib_stdarr.data());
}

TEST(array_ref, copy_constructor)
{
    auto aref                 = bte::array_ref(fib_stdarr);
    auto aref_copy_under_test = aref;

    EXPECT_THAT(aref_copy_under_test, ::testing::ElementsAreArray(fib_stdarr));
    EXPECT_EQ(aref_copy_under_test.data(), fib_stdarr.data());
}

TEST(array_ref, at_read)
{
    const auto aref_under_test = bte::array_ref(fib_stdarr);

    const auto neg_1_index = static_cast<std::size_t>(-1);
    const int  neg_1_value = -1;

    EXPECT_FALSE(aref_under_test.at(neg_1_index));
    EXPECT_EQ(aref_under_test.at(0u).value_or(neg_1_value), 1);
    EXPECT_EQ(aref_under_test.at(1u).value_or(neg_1_value), 1);
    EXPECT_EQ(aref_under_test.at(2u).value_or(neg_1_value), 2);
    EXPECT_EQ(aref_under_test.at(3u).value_or(neg_1_value), 3);
    EXPECT_EQ(aref_under_test.at(4u).value_or(neg_1_value), 5);
    EXPECT_EQ(aref_under_test.at(5u).value_or(neg_1_value), 8);
    EXPECT_EQ(aref_under_test.at(6u).value_or(neg_1_value), 13);
    EXPECT_EQ(aref_under_test.at(7u).value_or(neg_1_value), 21);
    EXPECT_FALSE(aref_under_test.at(8u));
}

TEST(array_ref, at_read_enum_index)
{
    const auto aref_under_test = bte::array_ref(fib_stdarr);
    const int  neg_1_value     = -1;

    enum class IDX
    {
        _neg_1 = -1,
        _0     = 0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8
    };

    EXPECT_FALSE(aref_under_test.at(IDX::_neg_1));
    EXPECT_EQ(aref_under_test.at(IDX::_0).value_or(neg_1_value), 1);
    EXPECT_EQ(aref_under_test.at(IDX::_1).value_or(neg_1_value), 1);
    EXPECT_EQ(aref_under_test.at(IDX::_2).value_or(neg_1_value), 2);
    EXPECT_EQ(aref_under_test.at(IDX::_3).value_or(neg_1_value), 3);
    EXPECT_EQ(aref_under_test.at(IDX::_4).value_or(neg_1_value), 5);
    EXPECT_EQ(aref_under_test.at(IDX::_5).value_or(neg_1_value), 8);
    EXPECT_EQ(aref_under_test.at(IDX::_6).value_or(neg_1_value), 13);
    EXPECT_EQ(aref_under_test.at(IDX::_7).value_or(neg_1_value), 21);
    EXPECT_FALSE(aref_under_test.at(IDX::_8));
}

TEST(array_ref, at_write)
{
    std::array<int, 4> arr = {0xAAAA, 0x5555, 0xAAAA, 0x5555};
    std::array<int, 4> arr_expected{0x5555, 0xAAAA, 0x5555, 0xAAAA};
    auto               aref_under_test = bte::array_ref(arr);

    EXPECT_THAT(aref_under_test, ::testing::ElementsAreArray(arr));
    aref_under_test
        .at(0u)                                     // std::optional<std::reference_wrapper<int>>
        .value()                                    // std::reference_wrapper<int>
        .get()                           = 0x5555;  // int& = 0x5555;
    aref_under_test.at(1u).value().get() = 0xAAAA;
    aref_under_test.at(2u).value().get() = 0x5555;
    aref_under_test.at(3u).value().get() = 0xAAAA;
    EXPECT_THAT(aref_under_test, ::testing::ElementsAreArray(arr_expected));
}

TEST(array_ref, at_write_enum_index)
{
    std::array<int, 4> arr = {0xAAAA, 0x5555, 0xAAAA, 0x5555};
    std::array<int, 4> arr_expected{0x5555, 0xAAAA, 0x5555, 0xAAAA};
    auto               aref_under_test = bte::array_ref(arr);

    enum class IDX
    {
        _0 = 0,
        _1,
        _2,
        _3
    };

    EXPECT_THAT(aref_under_test, ::testing::ElementsAreArray(arr));
    aref_under_test
        .at(IDX::_0)  // std::optional<std::reference_wrapper<int>>
        .value()      // std::reference_wrapper<int>
        .get()                                = 0x5555;  // int& = 0x5555;
    aref_under_test.at(IDX::_1).value().get() = 0xAAAA;
    aref_under_test.at(IDX::_2).value().get() = 0x5555;
    aref_under_test.at(IDX::_3).value().get() = 0xAAAA;
    EXPECT_THAT(aref_under_test, ::testing::ElementsAreArray(arr_expected));
}

TEST(array_ref, index_operator_read)
{
    // NOTE: no bounds checking in this test
    const auto aref_under_test = bte::array_ref(fib_stdarr);

    EXPECT_EQ(aref_under_test[0u], 1);
    EXPECT_EQ(aref_under_test[1u], 1);
    EXPECT_EQ(aref_under_test[2u], 2);
    EXPECT_EQ(aref_under_test[3u], 3);
    EXPECT_EQ(aref_under_test[4u], 5);
    EXPECT_EQ(aref_under_test[5u], 8);
    EXPECT_EQ(aref_under_test[6u], 13);
    EXPECT_EQ(aref_under_test[7u], 21);
}

TEST(array_ref, index_operator_read_enum_index)
{
    // NOTE: no bounds checking in this test
    const auto aref_under_test = bte::array_ref(fib_stdarr);

    enum class IDX
    {
        _0 = 0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8
    };

    EXPECT_EQ(aref_under_test[IDX::_0], 1);
    EXPECT_EQ(aref_under_test[IDX::_1], 1);
    EXPECT_EQ(aref_under_test[IDX::_2], 2);
    EXPECT_EQ(aref_under_test[IDX::_3], 3);
    EXPECT_EQ(aref_under_test[IDX::_4], 5);
    EXPECT_EQ(aref_under_test[IDX::_5], 8);
    EXPECT_EQ(aref_under_test[IDX::_6], 13);
    EXPECT_EQ(aref_under_test[IDX::_7], 21);
}

TEST(array_ref, index_operator_write)
{
    std::array<int, 4> arr = {0xAAAA, 0x5555, 0xAAAA, 0x5555};
    std::array<int, 4> arr_expected{0x5555, 0xAAAA, 0x5555, 0xAAAA};
    auto               aref_under_test = bte::array_ref(arr);

    EXPECT_THAT(aref_under_test, ::testing::ElementsAreArray(arr));
    aref_under_test[0u] = 0x5555;
    aref_under_test[1u] = 0xAAAA;
    aref_under_test[2u] = 0x5555;
    aref_under_test[3u] = 0xAAAA;
    EXPECT_THAT(aref_under_test, ::testing::ElementsAreArray(arr_expected));
}

TEST(array_ref, index_operator_write_enum_index)
{
    std::array<int, 4> arr = {0xAAAA, 0x5555, 0xAAAA, 0x5555};
    std::array<int, 4> arr_expected{0x5555, 0xAAAA, 0x5555, 0xAAAA};
    auto               aref_under_test = bte::array_ref(arr);

    enum class IDX
    {
        _0 = 0,
        _1,
        _2,
        _3
    };

    EXPECT_THAT(aref_under_test, ::testing::ElementsAreArray(arr));
    aref_under_test[IDX::_0] = 0x5555;
    aref_under_test[IDX::_1] = 0xAAAA;
    aref_under_test[IDX::_2] = 0x5555;
    aref_under_test[IDX::_3] = 0xAAAA;
    EXPECT_THAT(aref_under_test, ::testing::ElementsAreArray(arr_expected));
}

TEST(array_ref, to_index)
{
    const auto neg_1 = static_cast<std::size_t>(-1);

    auto aref_under_test = bte::array_ref(fib_stdarr);
    auto iter            = aref_under_test.end();

    EXPECT_FALSE(bte::to_index(aref_under_test, iter));
    EXPECT_EQ(bte::to_index(aref_under_test, --iter).value_or(neg_1), 7);
    EXPECT_EQ(bte::to_index(aref_under_test, --iter).value_or(neg_1), 6);
    EXPECT_EQ(bte::to_index(aref_under_test, --iter).value_or(neg_1), 5);
    EXPECT_EQ(bte::to_index(aref_under_test, --iter).value_or(neg_1), 4);
    EXPECT_EQ(bte::to_index(aref_under_test, --iter).value_or(neg_1), 3);
    EXPECT_EQ(bte::to_index(aref_under_test, --iter).value_or(neg_1), 2);
    EXPECT_EQ(bte::to_index(aref_under_test, --iter).value_or(neg_1), 1);
    EXPECT_EQ(bte::to_index(aref_under_test, --iter).value_or(neg_1), 0);
    EXPECT_FALSE(bte::to_index(aref_under_test, --iter));
    EXPECT_EQ(bte::to_index(aref_under_test, ++iter).value_or(neg_1), 0);
    EXPECT_EQ(bte::to_index(aref_under_test, ++iter).value_or(neg_1), 1);
    EXPECT_EQ(bte::to_index(aref_under_test, ++iter).value_or(neg_1), 2);
    EXPECT_EQ(bte::to_index(aref_under_test, ++iter).value_or(neg_1), 3);
    EXPECT_EQ(bte::to_index(aref_under_test, ++iter).value_or(neg_1), 4);
    EXPECT_EQ(bte::to_index(aref_under_test, ++iter).value_or(neg_1), 5);
    EXPECT_EQ(bte::to_index(aref_under_test, ++iter).value_or(neg_1), 6);
    EXPECT_EQ(bte::to_index(aref_under_test, ++iter).value_or(neg_1), 7);
    EXPECT_FALSE(bte::to_index(aref_under_test, ++iter));
}