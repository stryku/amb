#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TibiaFinder.hpp"
#include "ui/modules/healer/HealerRulesTable.hpp"
#include "ModuleId.hpp"
#include "ui/UiControls.hpp"

#include "ui/modules/looter/LooterCategoriesTable.hpp"
#include "ui/modules/looter/LooterItemsTable.hpp"

#include "db/Database.hpp"


#include <QMainWindow>
#include <QCheckBox>
#include <QtGlobal>
#include <QDebug>
#include <QCompleter>

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
    explicit MainWindow(const AMB::Db::Database &db, QWidget *parent = 0);
    ~MainWindow();

    const Ui::MainWindow* getUi() const;
    AMB::Ui::Controls::AdvancedSettings::Healer getAdvancedSettingsHealer() const;
    AMB::Ui::Controls::AdvancedSettings getAdvancedSettings() const;
    AMB::Ui::Controls::Looter getLotterControls() const;
    AMB::Ui::Controls::Healer getHealer() const;
    AMB::Ui::Controls::GlobalControls getControls() const;

    const AMB::Ui::Modules::Healer::HealerRulesTable& getHealerRulesTable() const;
    const AMB::Ui::Modules::Looter::LooterCategoriesTable& getLooterCategoriesTable() const;
    const AMB::Ui::Modules::Looter::LooterItemsTable& getLooterItemsTable() const;

    void setModuleToggleHandler( std::function<bool( AMB::Modules::ModuleId )> newHandler );
    void setTtibiaWindowChangedHandler(std::function<void(const std::wstring&)> newHandler);
    void setRefreshLayoutHandler(std::function<void()> newHandler);
    void setConfigProvider(std::function<std::string()> provider);
    void setConfigLoader( std::function<void(const std::string&)> loader);

    std::wstring getTibiaWindowTitle() const;

private slots:
    void on_checkBoxHealerRun_clicked();
    void on_cbTibiaClients_currentIndexChanged(const QString &arg1);
    void on_refreshLayoutButton_clicked();

    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionSave_as_triggered();
    void on_actionSave_triggered();

    void on_pushButtonHealerEdit_clicked();
    void on_pushButtonHealerUp_clicked();
    void on_pushButtonHealerDown_clicked();
    void on_btnRefreshClientsComboBox_clicked();
    void on_btnHealerAddRule_clicked();
    void on_btnHealerClear_clicked();

    void on_pushButtonLooterCategoriesNewCategoryAdd_clicked();
    void on_pushButtonLooterCategoriesEdit_clicked();
    void on_pushButtonLooterCategoriesClear_clicked();
    void on_pushButtonLooterItemsEdit_clicked();
    void on_pushButtonLooterItemsClear_clicked();
    void on_pushButtonLooterItemsAdd_clicked();


    void on_tabWidgetLooter_currentChanged(int index);

private:
    Ui::MainWindow *ui;

    QCompleter *itemsCompleter;

    const AMB::Db::Database &db;

    std::unique_ptr<AMB::Ui::Modules::Healer::HealerRulesTable> healerRulesTable;
    std::unique_ptr<AMB::Ui::Modules::Looter::LooterCategoriesTable> looterCategoriesTable;
    std::unique_ptr<AMB::Ui::Modules::Looter::LooterItemsTable> looterItemsTable;

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
