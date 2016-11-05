#pragma once

#include "ui/UiControls.hpp"
#include "Configs.hpp"
#include "utils/Structs.hpp"

namespace AMB
{
    namespace Ui
    {
        namespace Updaters
        {
            class AdvancedSettings
            {
            public:
                void update(const Configs::AdvancedSettings &advancedSettingsConfig, const Controls::AdvancedSettings &controls)
                {
                    auto str = QString::fromStdString(utils::toString(advancedSettingsConfig.healer.randBetweenChecks.from));
                    controls.healer.betweenChecks.from->setText(str);

                    str = QString::fromStdString(utils::toString(advancedSettingsConfig.healer.randBetweenChecks.to));
                    controls.healer.betweenChecks.to->setText(str);


                    str = QString::fromStdString(utils::toString(advancedSettingsConfig.healer.sleepAfterHotkey.from));
                    controls.healer.sleepAfterHotkey.from->setText(str);

                    str = QString::fromStdString(utils::toString(advancedSettingsConfig.healer.sleepAfterHotkey.from));
                    controls.healer.sleepAfterHotkey.to->setText(str);
                }
            };
        }
    }
}
