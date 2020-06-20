#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "beetree/test/behavior-reqs.hpp"

#include <map>
#include "beetree/registry/register-bank.hpp"
#include "registry/core/keyed-register-bank.hpp"

using registry::KeyedRegisterBank;
using registry::RegisterBankType;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

namespace RegisterBankTest {
enum class TestKeys
{
    ITEM_1,
    ITEM_2,
    ITEM_3,
    ITEM_4,
    NUM_ITEMS
};

class TestFixture : public unit_test::TestFixture
{
public:
    using TestBank = KeyedRegisterBank<RegisterBankType::MOTION, TestKeys>;

    TestBank bank;

    TestFixture() {}
};
}  // namespace RegisterBankTest

using RegisterBankTest::TestFixture;
using RegisterBankTest::TestKeys;

TEST(registry, RegisterBank_whenSettingAsUnsignedInteger_thenSignedIntegerIsReturned)
{
    TestFixture                 tf;
    std::map<uint32_t, int32_t> map{{0x7FFFFFFF, std::numeric_limits<int32_t>::max()},
                                    {0x80000000, std::numeric_limits<int32_t>::min()},
                                    {2, 2},
                                    {1, 1},
                                    {0, 0},
                                    {0xFFFFFFFF, -1},
                                    {0xFFFFFFFE, -2}};

    for (auto pair : map)
    {
        tf.bank[TestKeys::ITEM_1] = pair.first;
        int32_t result            = tf.bank[TestKeys::ITEM_1];
        EXPECT_EQ(result, pair.second);
    }
}

TEST(registry, BankLocator_whenSettingAsSignedInteger_thenUnsignedIntegerIsReturned)
{
    TestFixture                 tf;
    std::map<uint32_t, int32_t> map{{0x7FFFFFFF, std::numeric_limits<int32_t>::max()},
                                    {0x80000000, std::numeric_limits<int32_t>::min()},
                                    {2, 2},
                                    {1, 1},
                                    {0, 0},
                                    {0xFFFFFFFF, -1},
                                    {0xFFFFFFFE, -2}};

    for (auto pair : map)
    {
        tf.bank[TestKeys::ITEM_1] = pair.second;
        uint32_t result           = tf.bank[TestKeys::ITEM_1];
        EXPECT_EQ(result, pair.first);
    }
}