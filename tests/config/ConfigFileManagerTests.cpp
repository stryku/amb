#include <config/ConfigFileManager.hpp>
#include <tests/tests_related/utils/ObservatorMock.hpp>

#include <gtest/gtest.h>

#include <experimental/filesystem>
#include <vector>

namespace tests
{
    struct ConfigFileManagerTest : testing::Test
    {
        tests::Mock::Observator<std::experimental::filesystem::path> observer;
        Amb::Config::ConfigFileManager cfm;

        ConfigFileManagerTest()
            : cfm{ observer.getCallback() }
        {}
    };

    TEST_F(ConfigFileManagerTest, FreshCreated_PathEmpty)
    {
        ASSERT_TRUE(cfm.isPathEmpty());
    }

    TEST_F(ConfigFileManagerTest, FreshCreated_Save_DefaultPathParameter_NoThrow_NoWrite)
    {
        ASSERT_NO_THROW(cfm.save("some configs"));
        ASSERT_FALSE(cfm.save("some configs"));
    }

    namespace Save
    {
        namespace Once
        {
            struct ConfigFileManagerTestState
            {
                std::experimental::filesystem::path path;
                bool shouldSuccess;
            };

            struct ConfigFileManagerTest : testing::Test, testing::WithParamInterface<ConfigFileManagerTestState> {};

            TEST_P(ConfigFileManagerTest, SaveOnce)
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

        namespace Multiple
        {
            struct ConfigFileManagerTestState
            {
                struct SingleTestState
                {
                    std::experimental::filesystem::path observerValueBefore;
                    std::experimental::filesystem::path path;
                    bool shouldSuccess;
                    std::experimental::filesystem::path observerValueAfter;
                };

                std::vector<SingleTestState> states;
            };

            struct UpdateObservablePathTest : ConfigFileManagerTest, testing::WithParamInterface<ConfigFileManagerTestState> {};

            TEST_P(UpdateObservablePathTest, ObservablePathUpdate)
            {
                const auto state = GetParam();

                for (const auto& singleTestState : state.states)
                {
                    const auto result = cfm.save("some configs", singleTestState.path.string());
                    ASSERT_EQ(result, singleTestState.shouldSuccess);
                    ASSERT_EQ(singleTestState.observerValueAfter, observer.value);
                } 
            }

            INSTANTIATE_TEST_CASE_P(ConfigFileManager, UpdateObservablePathTest,
                                    testing::Values(
                                    ConfigFileManagerTestState{
                                        {
                                            ConfigFileManagerTestState::SingleTestState{ "", "", false, "" },
                                            ConfigFileManagerTestState::SingleTestState{ "", 
                                                                                         std::experimental::filesystem::temp_directory_path() / "file_0", 
                                                                                         true, 
                                                                                         std::experimental::filesystem::temp_directory_path() / "file_0" },
                                            ConfigFileManagerTestState::SingleTestState{ std::experimental::filesystem::temp_directory_path() / "file_0",
                                                                                         "",
                                                                                         true,
                                                                                         std::experimental::filesystem::temp_directory_path() / "file_0" },
                                            ConfigFileManagerTestState::SingleTestState{ std::experimental::filesystem::temp_directory_path() / "file_0",
                                                                                         std::experimental::filesystem::temp_directory_path() / "file_NEW",
                                                                                         true,
                                                                                         std::experimental::filesystem::temp_directory_path() / "file_NEW" }
                                        }}));
        }
    }
}
