#pragma once

class QLineEdit;
class QComboBox;
class QLabel;
class QCheckBox;

namespace Amb
{
    namespace Ui
    {
        namespace Module
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

namespace Amb
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
                    QComboBox *clientType;
                } common;
            };

            struct Healer
            {
                Amb::Ui::Module::Healer::HealerRulesTable *healerRulesTable;
            };

            struct Looter
            {
                Amb::Ui::Module::Looter::LooterItemsTable *looterItemsTable;
                Amb::Ui::Module::Looter::LooterCategoriesTable *looterCategoriesTable;
                QComboBox *categoriesCombobox;
            };

            struct Mlvl
            {
                QLineEdit *editMlvlManaFrom;
                QLineEdit *editMlvlManaTo;
                QComboBox *foodCombobox;
                QComboBox *spellCombobox;
            };

            struct MouseHotkeys
            {
                QLabel *capturedLabel;
                QCheckBox *onlyIfTibiaOnTop;
                QComboBox *hotCombobox;
            };

            struct GlobalControls
            {
                Healer healer;
                AdvancedSettings advancedSettings;
                Looter looter;
                Mlvl mlvl;
                MouseHotkeys mouseHotkeys;
            };
        }
    }
}
