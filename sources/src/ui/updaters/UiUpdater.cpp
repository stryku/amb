#include "ui/updaters/UiUpdater.hpp"
#include "ui/UiControls.hpp"
#include "Configs.hpp"

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            void UiUpdater::update(const Configs::GlobalConfig &config, const Controls::GlobalControls &controls)
            {
                healerUpdater.update(config.healerConfig, controls.healer);
                advSettingsUpdater.update(config.advancedSettings, controls.advancedSettings);
                looterUpdater.update(config.looter, controls.looter);
            }
        }
    }
}
