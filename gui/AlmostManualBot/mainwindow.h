#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TibiaFinder.hpp"
#include "HealerRulesTable.hpp"
#include "ModuleId.hpp"
#include "ui/UiControls.hpp"

#include "ui/modules/looter/LooterCategoriesTable.hpp"


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
    AMB::Ui::Controls::AdvancedSettings::Healer getAdvancedSettingsHealer() const;
    AMB::Ui::Controls::AdvancedSettings getAdvancedSettings() const;
    AMB::Ui::Controls::Healer getHealer() const;
    AMB::Ui::Controls::GlobalControls getControls() const;

    const HealerRulesTable& getHealerRulesTable() const;

    void setModuleToggleHandler( std::function<bool( AMB::Modules::ModuleId )> newHandler );
    void setTtibiaWindowChangedHandler(std::function<void(const std::wstring&)> newHandler);
    void setRefreshLayoutHandler(std::function<void()> newHandler);
    void setConfigProvider(std::function<std::string()> provider);
    void setConfigLoader( std::function<void(const std::string&)> loader);

    std::wstring getTibiaWindowTitle() const;

private slots:
    void on_btnRefreshClientsComboBox_clicked();
    void on_btnHealerAddRule_clicked();
    void on_btnHealerClear_clicked();
    void on_checkBoxHealerRun_clicked();
    void on_cbTibiaClients_currentIndexChanged(const QString &arg1);
    void on_refreshLayoutButton_clicked();
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionSave_as_triggered();
    void on_actionSave_triggered();

    void on_pushButtonLooterCategoriesNewCategoryAdd_clicked();
    void on_pushButtonLooterCategoriesEdit_clicked();
    void on_pushButtonLooterCategoriesClear_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<HealerRulesTable> healerRulesTable;
    std::unique_ptr<AMB::Ui::Modules::Looter::LooterCategoriesTable> looterCategoriesTable;
    std::function<bool(AMB::Modules::ModuleId)> moduleToggleHandler;
    std::function<void(const std::wstring&)> tibiaWindowChangedHandler;
    std::function<void()> refreshLayoutHandler;
    std::function<std::string()> configToSaveProvider;
    std::function<void(const std::string&)> configLoader;

    void updateTibiaClientsComboBox();
    void toggleHealer();
    bool startModule( QCheckBox *moduleCheckBox,
                      AMB::Modules::ModuleId modId );
    void stopModule( QCheckBox *moduleCheckBox,
                     AMB::Modules::ModuleId modId );
};

#endif // MAINWINDOW_H
