#pragma once

namespace Ui
{
    class MainWindow;
}

namespace Amb
{
    namespace Module
    {
        namespace UiRemover
        {
            class LooterUiRemover
            {
            public:
                void remove(::Ui::MainWindow *ui) const;
            };
        }
    }
}
