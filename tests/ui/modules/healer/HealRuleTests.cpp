#include "ui/modules/healer/HealRule.hpp"
#include "client/Hotkey.hpp"

#include <gtest/gtest.h>

using namespace Amb::Module::Heal;

namespace tests
{
    struct HealRuleTestState
    {
        HealRule rule;
        int hp;
        int mana;
        bool shouldPass;
    };

    struct HealRuleTest : testing::Test, testing::WithParamInterface<HealRuleTestState> {};

    TEST_P(HealRuleTest, Passed)
    {
        const auto state = GetParam();
        const auto result = state.rule.passed(state.hp, state.mana);
        ASSERT_EQ(result, state.shouldPass);
    }

    INSTANTIATE_TEST_CASE_P(HealRulea, HealRuleTest,
                            testing::Values(
                                HealRuleTestState{ HealRule(0, 100, 0, 100, Amb::Client::Hotkey::F1), 100, 0, true },
                                HealRuleTestState{ HealRule(0, 100, 0, 100, Amb::Client::Hotkey::F1), 0, 100, true },
                                HealRuleTestState{ HealRule(0, 100, 0, 100, Amb::Client::Hotkey::F1), 50, 101, false },
                                HealRuleTestState{ HealRule(0, 100, 0, 100, Amb::Client::Hotkey::F1), 101, 50, false }));
}
