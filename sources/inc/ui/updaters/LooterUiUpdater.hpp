#pragma once

#include "ui/UiControls.hpp"
#include "Configs.hpp"
#include "utils/Structs.hpp"
#include "ui/modules/looter/LooterCategoriesTable.hpp"
#include "ui/modules/looter/LooterItemsTable.hpp"

#include <QComboBox>

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            class Looter
            {
            public:
                void update(const Configs::Looter &configs, const Controls::Looter &controls)
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
            };
        }
    }
}
