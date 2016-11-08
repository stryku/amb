#pragma once

#include "ui/updaters/AdvancedSettingsUiUpdater.hpp"
#include "ui/updaters/HealerUiUpdater.hpp"
#include "ui/UiControls.hpp"

#include <QLineEdit>

namespace AMB
{
    namespace Ui
    {
        namespace Updaters
        {
            class UiUpdater
            {
            public:
                void update(const Configs::GlobalConfig &config, const Controls::GlobalControls &controls)
                {
                    healerUpdater.update(config.healerConfig, controls.healer);
                    advSettingsUpdater.update(config.advancedSettings, controls.advancedSettings);
                }

            private:
                Healer healerUpdater;
                AdvancedSettings advSettingsUpdater;
            };
        }
    }
}
