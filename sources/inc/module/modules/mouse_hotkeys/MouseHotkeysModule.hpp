#pragma once

#include "module/ModuleCore.hpp"
#include "log/details/Logger.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            struct MouseHotkeysConfig;
        }
    }

    namespace Module
    {
        namespace Modules
        {
            namespace MouseHotkeys
            {
                class MouseHotkeysModule final : public ModuleCore
                {
                public:
                    MouseHotkeysModule(Simulate::Simulator &simulator,
                                       const Client::TibiaClientWindowInfo &tibiaClientWindowInfo,
                                       const Config::Module::MouseHotkeysConfig& mouseHotkeysConfig);

                private:
                    void runDetails() override;
                    void applyConfigs() override;

                    const Config::Module::MouseHotkeysConfig& mouseHotkeysConfig;
                    Log::details::Logger logger;
                };
            }
        }
    }
}
