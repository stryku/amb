#include "module/modules/MlvlModule.hpp"

namespace Amb
{
    namespace Module
    {
        namespace Mlvl
        {
            MlvlModule::MlvlModule(const Configs::Looter &config,
                        const Configs::AdvancedSettings &advancedSettings,
                        std::unique_ptr<Client::Reader::TibiaClientReader> tibiaClientReader)
            {}

            void MlvlModule::attachToNewProcess(DWORD pid)
            {}
            void MlvlModule::setEnableDebugLogs(bool enabled)
            {}

            const Configs::Looter &config;
            const Configs::AdvancedSettings &advancedSettings;

            void MlvlModule::runDetails()
            {}
            void MlvlModule::applyConfigs()
            {}
        }
    }
}


