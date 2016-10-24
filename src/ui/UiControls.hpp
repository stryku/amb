#pragma once

class QLineEdit;

namespace AMB
{
    namespace Ui
    {
        namespace Controls
        {
            namespace AdvancedSettings
            {
                struct Healer
                {
                    struct
                    {
                        QLineEdit *from, *to;
                    }betweenChecks, sleepAfterHotkey;
                };
            }
        }
    }
}
