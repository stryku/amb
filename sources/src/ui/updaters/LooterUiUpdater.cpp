#include "ui/updaters/LooterUiUpdater.hpp"

#include "ui/UiControls.hpp"
#include "utils/Structs.hpp"
#include "ui/modules/looter/LooterCategoriesTable.hpp"
#include "ui/modules/looter/LooterItemsTable.hpp"
#include "config/module/LooterConfig.hpp"

#include <QComboBox>

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            void Looter::update(const Config::Module::LooterConfig &configs, const Controls::Looter &controls) const
            {
                for (const auto &item : configs.items)
                    controls.looterItemsTable->add(item);

                controls.categoriesCombobox->clear();

                for (const auto &cat : configs.categories)
                {
                    controls.looterCategoriesTable->add(cat);
                    controls.categoriesCombobox->addItem(QString::fromStdString(cat.name));
                }
            }
        }
    }
}
