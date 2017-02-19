#include <utils/Structs.hpp>

#include <gtest/gtest.h>

using namespace Amb;

namespace tests
{
    namespace RelativeToPoint
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

        INSTANTIATE_TEST_CASE_P(RelativeRect, RelativeToPointTest,
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

    namespace RelativeToRect
    {
        struct RelativeRectTestState
        {
            RelativeRect baseRect;
            RelativeRect relatoveToThis;
            Rect expected;
        };

        struct RelativeToRectTest : testing::Test, testing::WithParamInterface<RelativeRectTestState> {};

        TEST_P(RelativeToRectTest, RelativeToRect)
        {
            const auto state = GetParam();
            const auto result = state.baseRect.relativeToRect(state.relatoveToThis);
            ASSERT_EQ(result, state.expected);
        }

        INSTANTIATE_TEST_CASE_P(RelativeRect, RelativeToRectTest,
                                testing::Values(
                                    RelativeRectTestState{
                                        RelativeRect{ Pos{ 10, 20 }, Rect{ 100, 200, 300, 400 } },
                                        RelativeRect{ Pos{ 50, 70 }, Rect{ 100, 200, 300, 400 } },
                                        Rect{ -40, -50, 300, 400 }
                                    },
                                    RelativeRectTestState{
                                        RelativeRect{ Pos{ 100, 200 }, Rect{ -90, 150, 300, 400 } },
                                        RelativeRect{ Pos{ 100, 200 }, Rect{ -100, 0, 100, 800 } },
                                        Rect{ 10, 150, 300, 400 }
                                    }));
    }

    namespace RelativeToThis
    {
        struct RelativeRectTestState
        {
            RelativeRect baseRect;
            Pos point;
            Pos expected;
        };

        struct RelativeToThisTest : testing::Test, testing::WithParamInterface<RelativeRectTestState> {};

        TEST_P(RelativeToThisTest, RelativeToRect)
        {
            const auto state = GetParam();
            const auto result = state.baseRect.relativeToThis(state.point);
            ASSERT_EQ(result, state.expected);
        }

        INSTANTIATE_TEST_CASE_P(RelativeRect, RelativeToThisTest,
                                testing::Values(
                                    RelativeRectTestState{
                                        RelativeRect{ Pos{ 10, 20 }, Rect{ 100, 200, 300, 400 } },
                                        Pos{ 5, 5 },
                                        Pos{ 115, 225 }
                                    },
                                    RelativeRectTestState{
                                        RelativeRect{ Pos{ 10, 20 }, Rect{ 100, 200, 300, 400 } },
                                        Pos{ -600, -600 },
                                        Pos{ -490, -380 }
                                    }));
    }
}
