#include <utils/Structs.hpp>

#include <gtest/gtest.h>

TEST(Structs, Pos_EqOperators)
{
    Amb::Pos a, b;

    a = Amb::Pos{ 0,0 };
    b = Amb::Pos{ 0,0 };
    ASSERT_EQ(a, b);

    a = Amb::Pos{ 1,0 };
    b = Amb::Pos{ 0,0 };
    ASSERT_NE(a, b);

    a = Amb::Pos{ 0,1 };
    b = Amb::Pos{ 0,0 };
    ASSERT_NE(a, b);
}

TEST(Structs, Rect_EqOperators)
{
    Amb::Rect a, b;

    a = Amb::Rect{ 0, 0, 10, 10 };
    b = Amb::Rect{ 0, 0, 10, 10 };
    ASSERT_EQ(a, b);

    a = Amb::Rect{ 1, 0, 10, 10 };
    b = Amb::Rect{ 0, 0, 10, 10 };
    ASSERT_NE(a, b);

    a = Amb::Rect{ 0, 1, 10, 10 };
    b = Amb::Rect{ 0, 0, 10, 10 };
    ASSERT_NE(a, b);

    a = Amb::Rect{ 0, 0, 11, 10 };
    b = Amb::Rect{ 0, 0, 10, 10 };
    ASSERT_NE(a, b);

    a = Amb::Rect{ 0, 0, 10, 11 };
    b = Amb::Rect{ 0, 0, 10, 10 };
    ASSERT_NE(a, b);
}

TEST(Structs, Rect_CornersGetters)
{
    Amb::Rect a;
    Amb::Pos pos;

    a = Amb::Rect{ 0, 0, 10, 15 };

    pos = Amb::Pos{ 0, 0 };
    ASSERT_EQ(a.topLeft(), pos);

    pos = Amb::Pos{ 10, 0 };
    ASSERT_EQ(a.topRight(), pos);

    pos = Amb::Pos{ 0, 15 };
    ASSERT_EQ(a.bottomLeft(), pos);

    pos = Amb::Pos{ 10, 15 };
    ASSERT_EQ(a.bottomRight(), pos);
}

TEST(Structs, Rest_PlusOperator)
{
    const auto rect = Amb::Rect{ 10, 20, 30, 40 };
    const auto pos = Amb::Pos{ 100, 200 };
    const auto expected = Amb::Rect{ 110, 220, 30, 40 };

    const auto result = rect + pos;

    ASSERT_EQ(result, expected);
}
