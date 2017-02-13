﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TibiaFinder.hpp"
#include "ui/modules/healer/HealerRulesTable.hpp"
#include "module/ModuleId.hpp"
#include "ui/UiControls.hpp"

#include "ui/modules/looter/LooterCategoriesTable.hpp"
#include "ui/modules/looter/LooterItemsTable.hpp"

#include "db/Database.hpp"

#include "config/ConfigFileManager.hpp"

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
    explicit MainWindow(const Amb::Db::Database &db, QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow* getUi();
    Amb::Ui::Controls::AdvancedSettings::Healer getAdvancedSettingsHealer() const;
    Amb::Ui::Controls::AdvancedSettings::Common getAdvancedSettingsCommon() const;
    Amb::Ui::Controls::AdvancedSettings getAdvancedSettings() const;
    Amb::Ui::Controls::Looter getLotterControls() const;
    Amb::Ui::Controls::Healer getHealer() const;
    Amb::Ui::Controls::GlobalControls getControls() const;

    const Amb::Ui::Module::Healer::HealerRulesTable& getHealerRulesTable() const;
    const Amb::Ui::Module::Looter::LooterCategoriesTable& getLooterCategoriesTable() const;
    const Amb::Ui::Module::Looter::LooterItemsTable& getLooterItemsTable() const;

    void setModuleToggleHandler( std::function<bool( Amb::Module::ModuleId )> newHandler );
    void setTtibiaWindowChangedHandler(std::function<void(const std::wstring&)> newHandler);
    void setRefreshLayoutHandler(std::function<void()> newHandler);
    void setConfigProvider(std::function<std::string()> provider);
    void setCurrentConfigFilePathProvider(std::function<std::string()> provider);
    void setConfigLoader(std::function<void(const std::string&)> loader);
    void setScriptNameObserver(std::function<void(const std::string&)> observer);
    void setEnableDebugLogObserver(std::function<void(bool)> observer);

    std::wstring getTibiaWindowTitle() const;

private slots:
    void on_checkBoxHealerRun_clicked();
    void on_cbTibiaClients_currentIndexChanged(const QString &arg1);

    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionSave_as_triggered();
    void on_actionSave_triggered();
    void on_actionEnable_debug_logs_toggled(bool checked);

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

    void on_checkBoxLooterRunning_clicked();


private:
    Ui::MainWindow *ui;

    QCompleter *itemsCompleter;
    QCompleter *containersCompleter;

    const Amb::Db::Database &db;
    Amb::Config::ConfigFileManager configFileManager;

    std::unique_ptr<Amb::Ui::Module::Healer::HealerRulesTable> healerRulesTable;
    std::unique_ptr<Amb::Ui::Module::Looter::LooterCategoriesTable> looterCategoriesTable;
    std::unique_ptr<Amb::Ui::Module::Looter::LooterItemsTable> looterItemsTable;

    std::function<bool(Amb::Module::ModuleId)> moduleToggleHandler;
    std::function<void(const std::wstring&)> tibiaWindowChangedHandler;
    std::function<std::string()> configToSaveProvider;
    std::function<std::string()> currentConfigFilePathProvider;
    std::function<void(const std::string&)> configLoader;
    std::function<void(bool)> enableDebugLogObserver;

    void updateTibiaClientsComboBox();
    void toggleHealer();
    void toggleLooter();
    bool startModule( QCheckBox *moduleCheckBox,
                      Amb::Module::ModuleId modId );
    void stopModule( QCheckBox *moduleCheckBox,
                     Amb::Module::ModuleId modId );
};

#endif // MAINWINDOW_H
