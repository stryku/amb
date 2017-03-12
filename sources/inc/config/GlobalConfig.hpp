#pragma once

#include "utils/Observable.hpp"
#include "utils.hpp"
#include "ui/modules/healer/HealRule.hpp"
#include "utils/Structs.hpp"
#include "utils/PropertyTreeBuilder.hpp"

#include "ui/modules/looter/Category.hpp"
#include "ui/modules/looter/LootItem.hpp"
#include "capture/CaptureMode.hpp"
#include "client/TibiaClientWindowInfo.hpp"

#include "config/module/HealerConfig.hpp"
#include "config/module/AdvancedSettingsConfig.hpp"
#include "config/module/LooterConfig.hpp"
#include "config/module/MlvlConfig.hpp"
#include "config/module/MouseHotkeysConfig.hpp"

#include "client/TibiaClientType.hpp"



namespace Amb
{
    namespace Config
    {
        struct GlobalConfig
        {
            GlobalConfig(const Client::TibiaClientWindowInfo &tibiaClientWindowInfo);

            std::string toString() const;
            static GlobalConfig fromString(const std::string &str, 
                                           const Client::TibiaClientWindowInfo &info);

            DWORD pid{ NULL };
            HWND hwnd{ NULL };
            const Client::TibiaClientWindowInfo &tibiaClientWindowInfo;
            std::string currentConfigFilePath;
            std::string currentCharacterName;

            Config::Module::HealerConfig healerConfig;
            Config::Module::AdvancedSettingsConfig advancedSettings;
            Config::Module::LooterConfig looter;
            Config::Module::MlvlConfig mlvl;
            Config::Module::MouseHotkeysConfig mouseHotkeys;
        };
    }
}
