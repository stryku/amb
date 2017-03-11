#include "ui/updaters/HealerUiUpdater.hpp"

#include "ui/UiControls.hpp"
#include "Configs.hpp"
#include "ui/modules/healer/HealerRulesTable.hpp"
#include "config/module/HealerConfig.hpp"

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            void Healer::update(const Config::Module::HealerConfig &healerConfigs,
                                const Controls::Healer &healerControls) const
            {
                for (const auto &rule : healerConfigs.rules)
                    healerControls.healerRulesTable->add(rule);
            }
        }
    }
}
