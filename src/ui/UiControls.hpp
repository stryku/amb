#pragma once

class QLineEdit;
class HealerRulesTable;

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
                HealerRulesTable *healerRulesTable;
            };

            struct GlobalControls
            {
                Healer healer;
                AdvancedSettings advancedSettings;
            };
        }
    }
}
