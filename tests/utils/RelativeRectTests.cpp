#include <utils/Structs.hpp>

#include <gtest/gtest.h>

using namespace Amb;

namespace tests
{
    struct RelativeRectTestState
    {
        RelativeRect baseRect;
        Pos point;
        Rect expected;
    };

    struct RelativeToPointTest : testing::Test, testing::WithParamInterface<RelativeRectTestState> {};

    TEST_P(RelativeToPointTest, RelativeToPoint)
    {
        const auto state = GetParam();
        const auto result = state.baseRect.relativeToPoint(state.point);
        ASSERT_EQ(result, state.expected);
    }

    INSTANTIATE_TEST_CASE_P(Default, RelativeToPointTest,
                            testing::Values(
                                RelativeRectTestState{
                                    RelativeRect{ Pos{ 10, 20 }, Rect{ 100, 200, 300, 400 } },
                                    Pos{ 50, 70 },
                                    Rect{ 60, 150, 300, 400 }
                                },
                                RelativeRectTestState{
                                    RelativeRect{ Pos{ 10, 20 }, Rect{ 100, 200, 300, 400 } },
                                    Pos{ 500, 700 },
                                    Rect{ -390, -480, 300, 400 }
                                }));
}
