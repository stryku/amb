#include "config/module/AdvancedSettingsConfig.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            void AdvancedSettingsConfig::toPropertyTreeBuilder(Utils::PropertyTreeBuilder &builder, const std::string &path) const
            {
                healer.randBetweenChecks.toPropertyTreeBuilder(builder, path + ".healer.rand_between_checks");
                healer.sleepAfterHotkey.toPropertyTreeBuilder(builder, path + ".healer.sleep_after_hotkey");
                common.captureMode.toPropertyTreeBuilder(builder, path + ".common");
                Amb::Client::toPropertyTreeBuilder(builder, common.clientType, path + ".common");
            }

            AdvancedSettingsConfig AdvancedSettingsConfig::fromPtree(boost::property_tree::ptree &tree)
            {
                AdvancedSettingsConfig ret;

                ret.healer.randBetweenChecks = FromTo::fromPtree(tree.get_child("healer.rand_between_checks"));
                ret.healer.sleepAfterHotkey = FromTo::fromPtree(tree.get_child("healer.sleep_after_hotkey"));

                ret.common.captureMode = Capture::Mode::fromPtree(tree.get_child("common"));
                ret.common.clientType = Amb::Client::fromPtree(tree.get_child("common"));

                return ret;
            }
        }
    }
}
