#ifndef MAINWINDOW_H
#define MAINWINDOW_H




#include "TibiaFinder.hpp"
#include "HealerRulesTable.hpp"
#include "ModuleId.hpp"
#include "ui/UiControls.hpp"


#include <QMainWindow>
#include <QCheckBox>
#include <QtGlobal>
#include <QDebug>

#include <memory>
#include <functional>
#include <string>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    const Ui::MainWindow* getUi() const;
    const AMB::Ui::Controls::AdvancedSettings::Healer getAdvancedSettingsHealer() const;

    const HealerRulesTable& getHealerRulesTable() const;

    void setModuleToggleHandler( std::function<void( AMB::Modules::ModuleId )> newHandler );
    void setTtibiaWindowChangedHandler(std::function<void(const std::wstring&)> newHandler);
    void setRefreshLayoutHandler( std::function<void()> refreshLayoutHandler);

    std::wstring getTibiaWindowTitle() const;

private slots:
    void on_btnRefreshClientsComboBox_clicked();

    void on_btnHealerAddRule_clicked();

    void on_btnHealerClear_clicked();

    void on_checkBoxHealerRun_clicked();

    void on_cbTibiaClients_currentIndexChanged(const QString &arg1);

    void on_refreshLayoutButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<HealerRulesTable> healerRulesTable;
    std::function<void(AMB::Modules::ModuleId)> moduleToggleHandler;
    std::function<void(const std::wstring&)> tibiaWindowChangedHandler;
    std::function<void()> refreshLayoutHandler;

    void updateTibiaClientsComboBox();
    void toggleHealer();
    void startModule( QCheckBox *moduleCheckBox,
                      AMB::Modules::ModuleId modId );
    void stopModule( QCheckBox *moduleCheckBox,
                     AMB::Modules::ModuleId modId );
};

#endif // MAINWINDOW_H
