#pragma once

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            struct AdvancedSettingsConfig;
        }
    }

    namespace Ui
    {
        namespace Controls
        {
            struct AdvancedSettings;
        }

        namespace Updaters
        {
            class AdvancedSettings
            {
            public:
                void update(const Config::Module::AdvancedSettingsConfig &advancedSettingsConfig,
                            const Controls::AdvancedSettings &controls) const;
            };
        }
    }
}
