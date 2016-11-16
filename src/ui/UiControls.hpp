#pragma once

class QLineEdit;
class QComboBox;

namespace AMB
{
    namespace Ui
    {
        namespace Modules
        {
            namespace Healer
            {
                class HealerRulesTable;
            }

            namespace Looter
            {
                class LooterItemsTable;
                class LooterCategoriesTable;
            }
        }
    }
}

namespace AMB
{
    namespace Ui
    {
        namespace Controls
        {
            struct AdvancedSettings
            {
                struct Healer
                {
                    struct
                    {
                        QLineEdit *from, *to;
                    }betweenChecks, sleepAfterHotkey;
                } healer;

                struct Common
                {
                    QComboBox *captureMode;
                } common;
            };

            struct Healer
            {
                AMB::Ui::Modules::Healer::HealerRulesTable *healerRulesTable;
            };

            struct Looter
            {
                AMB::Ui::Modules::Looter::LooterItemsTable *looterItemsTable;
                AMB::Ui::Modules::Looter::LooterCategoriesTable *looterCategoriesTable;
                QComboBox *categoriesCombobox;
            };

            struct GlobalControls
            {
                Healer healer;
                AdvancedSettings advancedSettings;
                Looter looter;
            };
        }
    }
}
