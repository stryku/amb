#include <utils/Structs.hpp>
#include <gtest/gtest.h>

TEST(structs_pos, operators)
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
