#pragma once

#include "ui/updaters/AdvancedSettingsUiUpdater.hpp"
#include "ui/updaters/HealerUiUpdater.hpp"
#include "ui/updaters/LooterUiUpdater.hpp"
#include "ui/UiControls.hpp"

#include <QLineEdit>

namespace Amb
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
                    looterUpdater.update(config.looter, controls.looter);
                }

            private:
                Healer healerUpdater;
                AdvancedSettings advSettingsUpdater;
                Looter looterUpdater;
            };
        }
    }
}
