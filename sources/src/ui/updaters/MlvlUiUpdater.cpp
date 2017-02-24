#include "ui/updaters/MlvlUiUpdater.hpp"

#include "ui/UiControls.hpp"
#include "Configs.hpp"

#include <QComboBox>

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            void Mlvl::update(const Configs::Mlvl &configs, const Controls::Mlvl &controls) const
            {
                controls.manaPercent->setText(QString::number(configs.manaPercent));

                controls.spellCombobox->setCurrentIndex(Utils::hotkeyToSize_t(configs.spellHotkey));
                controls.foodCombobox->setCurrentIndex(Utils::hotkeyToSize_t(configs.foodHotkey));
            }
        }
    }
}
