#pragma once

namespace Amb
{
    namespace Configs
    {
        struct AdvancedSettings;
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
                void update(const Configs::AdvancedSettings &advancedSettingsConfig, 
                            const Controls::AdvancedSettings &controls) const;
            };
        }
    }
}
