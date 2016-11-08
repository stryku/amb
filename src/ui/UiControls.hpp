#pragma once

class QLineEdit;

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
            };

            struct Healer
            {
                AMB::Ui::Modules::Healer::HealerRulesTable *healerRulesTable;
            };

            struct GlobalControls
            {
                Healer healer;
                AdvancedSettings advancedSettings;
            };
        }
    }
}
