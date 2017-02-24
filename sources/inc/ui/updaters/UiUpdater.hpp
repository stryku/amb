#pragma once

#include "ui/updaters/AdvancedSettingsUiUpdater.hpp"
#include "ui/updaters/HealerUiUpdater.hpp"
#include "ui/updaters/LooterUiUpdater.hpp"

#include <QLineEdit>

namespace Amb
{
    namespace Configs
    {
        struct GlobalConfig;
    }

    namespace Ui
    {
        namespace Controls
        {
            struct GlobalControls;
        }

        namespace Updaters
        {
            class UiUpdater
            {
            public:
                void update(const Configs::GlobalConfig &config, const Controls::GlobalControls &controls);

            private:
                Healer healerUpdater;
                AdvancedSettings advSettingsUpdater;
                Looter looterUpdater;
            };
        }
    }
}
