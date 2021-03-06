#include "ui/updaters/MlvlUiUpdater.hpp"


#include "ui/UiControls.hpp"
#include "config/module/MlvlConfig.hpp"

#include <QComboBox>
#include <QLineEdit>

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            void Mlvl::update(const Config::Module::MlvlConfig &configs, const Controls::Mlvl &controls) const
            {
                controls.editMlvlManaFrom->setText(QString::number(configs.manaPercentFrom));
                controls.editMlvlManaTo->setText(QString::number(configs.manaPercentTo));

                controls.spellCombobox->setCurrentIndex(Client::hotkeyToSize_t(configs.spellHotkey));
                controls.foodCombobox->setCurrentIndex(Client::hotkeyToSize_t(configs.foodHotkey));
            }
        }
    }
}
