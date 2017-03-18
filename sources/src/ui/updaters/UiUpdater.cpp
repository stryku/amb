#include "ui/updaters/UiUpdater.hpp"
#include "ui/UiControls.hpp"
#include "config/GlobalConfig.hpp"

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            void UiUpdater::update(const Config::GlobalConfig &config, const Controls::GlobalControls &controls)
            {
                healerUpdater.update(config.healerConfig, controls.healer);
                advSettingsUpdater.update(config.advancedSettings, controls.advancedSettings);
                looterUpdater.update(config.looter, controls.looter);
                mlvlUpdater.update(config.mlvl, controls.mlvl);
            }
        }
    }
}
