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
                controls.editMlvlManaFrom->setText(QString::number(configs.manaPercentFrom));
                controls.editMlvlManaTo->setText(QString::number(configs.manaPercentTo));

                controls.spellCombobox->setCurrentIndex(Utils::hotkeyToSize_t(configs.spellHotkey));
                controls.foodCombobox->setCurrentIndex(Utils::hotkeyToSize_t(configs.foodHotkey));
            }
        }
    }
}
