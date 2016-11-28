#include "module/modules/LooterModule.hpp"

#include <chrono>

namespace Amb
{
    namespace Module
    {
        namespace Looter
        {
            LooterModule::LooterModule(const Configs::Looter &config,
                                       const Configs::AdvancedSettings &advancedSettings,
                                       Simulate::Simulator &simulator,
                                       const Client::TibiaClientWindowInfo &tibiaClientWindowInfo)
                : ModuleCore{ simulator, tibiaClientWindowInfo }
                , reader{ items }
                , config{ config }
                , advancedSettings{ advancedSettings }
            {}

            void LooterModule::attachToNewWindow(HWND hwnd)
            {
                reader.attachToNewWindow(hwnd);
            }

            void runDetails()
            {

            }

            void applyConfigs()
            {

            }
        }
    }
}


