#include <config/ConfigFileManager.hpp>

#include <gtest/gtest.h>

#include <experimental/filesystem>

namespace tests
{
    TEST(ConfigFileManager, FreshCreated_PathEmpty)
    {
        Amb::Config::ConfigFileManager cfm;
        ASSERT_TRUE(cfm.isPathEmpty());
    }

    TEST(ConfigFileManager, FreshCreated_Save_DefaultPathParameter_NoThrow_NoWrite)
    {
        Amb::Config::ConfigFileManager cfm;
        ASSERT_NO_THROW(cfm.save("some configs"));
        ASSERT_FALSE(cfm.save("some configs"));
    }

    namespace Save
    {
        struct ConfigFileManagerTestState
        {
            std::experimental::filesystem::path path;
            bool shouldSuccess;
        };

        struct ConfigFileManagerTest : testing::Test, testing::WithParamInterface<ConfigFileManagerTestState> {};

        TEST_P(ConfigFileManagerTest, Save)
        {
            const auto state = GetParam();
            Amb::Config::ConfigFileManager cfm;

            ASSERT_NO_THROW(cfm.save("some configs", state.path.string()));
            const auto result = cfm.save("some configs", state.path.string());
            ASSERT_EQ(result, state.shouldSuccess);
        }

        INSTANTIATE_TEST_CASE_P(ConfigFileManager, ConfigFileManagerTest,
                                testing::Values(
                                ConfigFileManagerTestState{ "", false },
                                ConfigFileManagerTestState{ std::experimental::filesystem::temp_directory_path() / "ok_file_path.xml", true }
                                ));
    }
}
