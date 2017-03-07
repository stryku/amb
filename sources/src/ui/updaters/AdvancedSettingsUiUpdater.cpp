#include "ui/updaters/AdvancedSettingsUiUpdater.hpp"

#include "ui/UiControls.hpp"
#include "Configs.hpp"

#include <QComboBox>

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            void AdvancedSettings::update(const Configs::AdvancedSettings &advancedSettingsConfig, 
                                          const Controls::AdvancedSettings &controls) const
            {
                auto str = QString::fromStdString(utils::toString(advancedSettingsConfig.healer.randBetweenChecks.from));
                controls.healer.betweenChecks.from->setText(str);

                str = QString::fromStdString(utils::toString(advancedSettingsConfig.healer.randBetweenChecks.to));
                controls.healer.betweenChecks.to->setText(str);


                str = QString::fromStdString(utils::toString(advancedSettingsConfig.healer.sleepAfterHotkey.from));
                controls.healer.sleepAfterHotkey.from->setText(str);

                str = QString::fromStdString(utils::toString(advancedSettingsConfig.healer.sleepAfterHotkey.from));
                controls.healer.sleepAfterHotkey.to->setText(str);

                const auto val = static_cast<int>(advancedSettingsConfig.common.captureMode.toSize_t());
                controls.common.captureMode->setCurrentIndex(val);

                const auto client = static_cast<int>(Amb::Client::toSize_t(advancedSettingsConfig.common.clientType));
                controls.common.clientType->setCurrentIndex(val);
            }
        }
    }
}
