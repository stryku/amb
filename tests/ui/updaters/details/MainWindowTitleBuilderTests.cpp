#include <ui/updaters/details/MainWindowTitleBuilder.hpp>

#include <gtest/gtest.h>

#include <string>

namespace tests
{
    TEST(MainWindowTitleBuilder, empty)
    {
        Amb::Ui::Updaters::details::MainWindowTitleBuilder builder;
        const auto result = builder.build();

        std::string expected = "AMB";
        expected += AMB_VERSION;

        ASSERT_EQ(result, expected);
    }

    TEST(MainWindowTitleBuilder, EmptyCharFullScript)
    {
        Amb::Ui::Updaters::details::MainWindowTitleBuilder builder;

        builder.withScriptName("script");
        auto result = builder.build();

        std::string expected = "AMB";
        expected += AMB_VERSION;
        expected += " (script)";

        ASSERT_EQ(result, expected);

        builder.withCharacterName("");
        result = builder.build();

        ASSERT_EQ(result, expected);

    }

    TEST(MainWindowTitleBuilder, FullCharEmptyScript)
    {
        Amb::Ui::Updaters::details::MainWindowTitleBuilder builder;

        builder.withCharacterName("name");
        auto result = builder.build();

        std::string expected = "AMB";
        expected += AMB_VERSION;
        expected += " - name";

        ASSERT_EQ(result, expected);


        builder.withScriptName("");
        result = builder.build();

        ASSERT_EQ(result, expected);
    }

    TEST(MainWindowTitleBuilder, FullCharFullScript)
    {
        Amb::Ui::Updaters::details::MainWindowTitleBuilder builder;

        builder.withCharacterName("name")
               .withScriptName("script");
        auto result = builder.build();

        std::string expected = "AMB";
        expected += AMB_VERSION;
        expected += " - name (script)";

        ASSERT_EQ(result, expected);
    }
}
