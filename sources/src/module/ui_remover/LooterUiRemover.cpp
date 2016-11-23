#include "module/ui_remover/LooterUiRemover.hpp"

#include "ui_mainwindow.h"

namespace Amb
{
    namespace Module
    {
        namespace UiRemover
        {
            void LooterUiRemover::remove(::Ui::MainWindow *ui) const
            {
                const size_t looterTabIndex = 1;
                ui->tabWidget->removeTab(looterTabIndex);
            }
        }
    }
}
