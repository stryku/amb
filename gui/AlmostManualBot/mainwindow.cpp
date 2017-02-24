#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "log/log.hpp"

#include "utils.hpp"

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include <algorithm>
#include <experimental/filesystem>

namespace
{
    template <typename Container, typename Parent>
    QCompleter* createCompleter(const Container &container, Parent *parent)
    {
        QCompleter *completer;
        QStringList strList;

        strList.reserve(container.size());

        for (const auto &item : container)
            strList << QString::fromStdString(item);

        completer = new QCompleter(strList, parent);
        completer->setCaseSensitivity(Qt::CaseInsensitive);

        return completer;
    }
}

MainWindow::MainWindow(const Amb::Db::Database &db, QWidget *parent)
    : QMainWindow(parent)
    , ui{ new Ui::MainWindow }
    , db{ db }
{
    ui->setupUi(this);

    healerRulesTable = std::make_unique<Amb::Ui::Module::Healer::HealerRulesTable>(ui->tableHealerRules);
    looterCategoriesTable = std::make_unique<Amb::Ui::Module::Looter::LooterCategoriesTable>(ui->tableViewLooterCategoriesCategoriesList);
    looterItemsTable = std::make_unique<Amb::Ui::Module::Looter::LooterItemsTable>(ui->tableLooterItems);
    
    itemsCompleter = createCompleter(db.items.getNames(), this);
    ui->editLooterItemsItem->setCompleter(itemsCompleter);

    containersCompleter = createCompleter(db.containers.getNames(), this);
    ui->editLooterCategoriesNewCategoryDestination->setCompleter(containersCompleter);

    clientComboboxUpdater.setCombobox(ui->cbTibiaClients);
    updateTibiaClientsComboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTibiaClientsComboBox()
{
    const auto hideNick = ui->actionHide_nick->isChecked();
    clientComboboxUpdater.update(hideNick);
}

void MainWindow::on_btnRefreshClientsComboBox_clicked()
{
    updateTibiaClientsComboBox();
}

void MainWindow::on_btnHealerAddRule_clicked()
{
    const auto hotkeyCombo = ui->cbHealerHotkey;

    size_t minHeal = ui->spinBoxHealerMinHp->value();
    size_t maxHeal = ui->spinBoxHealerMaxHp->value();
    size_t minMana = ui->spinBoxHealerMinMana->value();
    size_t maxMana = ui->spinBoxHealerMaxMana->value();

    if (minHeal >= maxHeal || minMana >= maxMana)
    {
        QMessageBox::information(this, "Error", "This rule is invalid.", QMessageBox::Ok);
        return;
    }

    auto hotkey = hotkeyCombo->currentIndex();

    healerRulesTable->add(minHeal,
                          maxHeal,
                          minMana,
                          maxMana,
                          hotkey);
}

void MainWindow::on_btnHealerClear_clicked()
{
    healerRulesTable->clear();
}

void MainWindow::toggleHealer()
{
    if( !ui->checkBoxHealerRun->isChecked() )
    {
        stopModule( ui->checkBoxHealerRun,
                    Amb::Module::ModuleId::MOD_HEALER );
    }
    else
    {
        if (!startModule(ui->checkBoxHealerRun,
                         Amb::Module::ModuleId::MOD_HEALER))
        {
            ui->checkBoxHealerRun->setChecked(false);
        }
    }
}

bool MainWindow::startModule( QCheckBox *moduleCheckBox,
                              Amb::Module::ModuleId modId )
{
    if (moduleToggleHandler(modId))
    {
        auto p = moduleCheckBox->palette();

        p.setColor(QPalette::Active, QPalette::WindowText, QColor("green"));
        moduleCheckBox->setPalette(p);
        moduleCheckBox->setText("Running");
        return true;
    }
    else
    {
        auto p = moduleCheckBox->palette();

        p.setColor(QPalette::Active, QPalette::WindowText, QColor("black"));
        moduleCheckBox->setPalette(p);
        moduleCheckBox->setText("Not running");
        return false;
    }
}

void MainWindow::stopModule( QCheckBox *moduleCheckBox,
                             Amb::Module::ModuleId modId )
{
    auto p = moduleCheckBox->palette();

    p.setColor( QPalette::Active, QPalette::WindowText, QColor( "red" ) );
    moduleCheckBox->setPalette( p );
    moduleCheckBox->setText( "Not Running" );

    moduleToggleHandler( modId );
}

Ui::MainWindow* MainWindow::getUi()
{
    return ui;
}

Amb::Ui::Controls::AdvancedSettings::Healer MainWindow::getAdvancedSettingsHealer() const
{
    Amb::Ui::Controls::AdvancedSettings::Healer healer;

    healer.betweenChecks.from = ui->editRandBeetwenChecksFrom;
    healer.betweenChecks.to = ui->editRandBeetwenChecksTo;

    healer.sleepAfterHotkey.from = ui->editSleepAfterHotkeyFrom;
    healer.sleepAfterHotkey.to = ui->editSleepAfterHotkeyTo;

    return healer;
}

Amb::Ui::Controls::AdvancedSettings::Common MainWindow::getAdvancedSettingsCommon() const
{
    Amb::Ui::Controls::AdvancedSettings::Common config;

    config.captureMode = ui->comboBoxAdvancedSettingsCaptureMode;
    config.clientType = ui->comboBoxAdvancedSettingsCommonTibiaClient;

    return config;
}

Amb::Ui::Controls::AdvancedSettings MainWindow::getAdvancedSettings() const
{
    Amb::Ui::Controls::AdvancedSettings controls;

    controls.healer = getAdvancedSettingsHealer();
    controls.common = getAdvancedSettingsCommon();

    return controls;
}

Amb::Ui::Controls::Mlvl MainWindow::getMlvlControls() const
{
    Amb::Ui::Controls::Mlvl controls;

    controls.manaPercent = ui->editMlvlMana;
    controls.foodCombobox = ui->cbMlvlFoodHotkey;
    controls.spellCombobox = ui->cbMlvSpelllHotkey;

    return controls;
}


Amb::Ui::Controls::Looter MainWindow::getLotterControls() const
{
    Amb::Ui::Controls::Looter controls;

    controls.looterCategoriesTable = looterCategoriesTable.get();
    controls.looterItemsTable = looterItemsTable.get();
    controls.categoriesCombobox = ui->comboBoxLooterItemsCategories;

    return controls;
}


Amb::Ui::Controls::Healer MainWindow::getHealer() const
{
    Amb::Ui::Controls::Healer healer;

    healer.healerRulesTable = healerRulesTable.get();

    return healer;
}

Amb::Ui::Controls::GlobalControls MainWindow::getControls() const
{
    Amb::Ui::Controls::GlobalControls controls;

    controls.healer = getHealer();
    controls.advancedSettings = getAdvancedSettings();
    controls.looter = getLotterControls();
    controls.mlvl = getMlvlControls();

    return controls;
}


const Amb::Ui::Module::Healer::HealerRulesTable& MainWindow::getHealerRulesTable() const
{
    return *(healerRulesTable.get());
}

const Amb::Ui::Module::Looter::LooterCategoriesTable& MainWindow::getLooterCategoriesTable() const
{
    return *(looterCategoriesTable.get());
}

const Amb::Ui::Module::Looter::LooterItemsTable& MainWindow::getLooterItemsTable() const
{
    return *(looterItemsTable.get());
}

void MainWindow::setScriptNameObserver(std::function<void(const std::string&)> observer)
{
    configFileManager.setPathObserver(
    [this, observer](const std::string &path)
    {
        const auto filename = std::experimental::filesystem::path(path).filename();
        observer(filename.string());
    });
}

void MainWindow::setModuleToggleHandler( std::function<bool( Amb::Module::ModuleId )> newHandler )
{
    moduleToggleHandler = newHandler;
}


void MainWindow::setTtibiaWindowChangedHandler( std::function<void(const std::wstring&)> newHandler )
{
    tibiaWindowChangedHandler = newHandler;
}

void MainWindow::setConfigProvider(std::function<std::string()> provider)
{
    configToSaveProvider = provider;
}
void MainWindow::setCurrentConfigFilePathProvider(std::function<std::string()> provider)
{
    currentConfigFilePathProvider = provider;
}

void MainWindow::setConfigLoader(std::function<void(const std::string&)> loader)
{
    configLoader = loader;
}

std::wstring MainWindow::getTibiaWindowTitle() const
{
    const auto cbTibiaClients = ui->cbTibiaClients;
    auto variant = cbTibiaClients->currentData();

    return variant.toString().toStdWString();
}

void MainWindow::on_checkBoxHealerRun_clicked()
{
    toggleHealer();
}

void MainWindow::on_cbTibiaClients_currentIndexChanged( const QString &arg1 )
{
    try
    {
        tibiaWindowChangedHandler( arg1.toStdWString() );
    }
    catch( std::bad_function_call &e )
    {
        LOG_DEBUG("Catch std::bad_function_call: %s", e.what());
    }
    catch( std::exception &e )
    {
        LOG_DEBUG("Catch std::exception: %s", e.what());
    }
}

void MainWindow::on_actionOpen_triggered()
{
    auto path = QFileDialog::getOpenFileName(this, 
                                             "Open file", 
                                             { "./configurations" }, 
                                             "*.amb");

    if (!path.length() == 0)
    {
        auto fileContent = configFileManager.load(path.toStdString());
        configLoader(fileContent);
    }
}

void MainWindow::on_actionExit_triggered()
{

}

void MainWindow::on_actionSave_as_triggered()
{
    assert(configToSaveProvider);

    auto path = QFileDialog::getSaveFileName(this,
                                             "Save file",
                                             "./configurations",
                                             "*.amb");

    if (!path.length() == 0)
    {
        const auto config = configToSaveProvider();
        configFileManager.save(config, path.toStdString());
    }
}

void MainWindow::on_actionSave_triggered()
{
    assert(currentConfigFilePathProvider);

    const auto currentPath = currentConfigFilePathProvider();

    if (configFileManager.isPathEmpty())
        on_actionSave_as_triggered();

    const auto config = configToSaveProvider();
    configFileManager.save(config);
}

void MainWindow::on_pushButtonLooterCategoriesNewCategoryAdd_clicked()
{
    Amb::Ui::Module::Looter::Category category;

    const auto name = ui->editLooterCategoriesNewCategorName->text();

    if (looterCategoriesTable->categoryExists(name.toStdString()))
    {
        auto msg = QString("Category '%1' already exist.").arg(name);
        QMessageBox::information(this, "Error", msg, QMessageBox::Ok);
        return;
    }

    const auto destination = ui->editLooterCategoriesNewCategoryDestination->text();

    if (!db.containers.existByName(destination.toStdString()))
    {
        auto msg = QString("Container '%1' doesn't exist.").arg(destination);
        QMessageBox::information(this, "Error", msg, QMessageBox::Ok);
        return;
    }

    category.name = name.toStdString();
    category.destination = destination.toStdString();
    category.toOnto = ui->comboBoxLooterCategoriesToOnto->currentIndex();

    looterCategoriesTable->add(category);
}

void MainWindow::on_pushButtonLooterCategoriesEdit_clicked()
{
    if (looterCategoriesTable->isSelectedEditable())
    {
        const auto category = looterCategoriesTable->getSelectedCategoryForEdit();

        ui->editLooterCategoriesNewCategorName->setText(QString::fromStdString(category.name));
        ui->editLooterCategoriesNewCategoryDestination->setText(QString::fromStdString(category.destination));
        ui->comboBoxLooterCategoriesToOnto->setCurrentIndex(static_cast<int>(category.toOnto));
    }
}

void MainWindow::on_pushButtonLooterCategoriesClear_clicked()
{
    looterCategoriesTable->clear();
}

void MainWindow::on_pushButtonHealerEdit_clicked()
{
    if (healerRulesTable->isSelectedEditable())
    {
        const auto rule = healerRulesTable->getSelectedForEdit();

        ui->spinBoxHealerMinHp->setValue(rule.minHp);
        ui->spinBoxHealerMaxHp->setValue(rule.maxHp);
        ui->spinBoxHealerMinMana->setValue(rule.minMana);
        ui->spinBoxHealerMaxMana->setValue(rule.maxMana);
        ui->cbHealerHotkey->setCurrentIndex(static_cast<int>(Amb::Utils::hotkeyToSize_t(rule.hotkey)));
    }
}

void MainWindow::on_pushButtonHealerUp_clicked()
{
    healerRulesTable->moveSelectedRowByOffset(-1);
}

void MainWindow::on_pushButtonHealerDown_clicked()
{
    healerRulesTable->moveSelectedRowByOffset(1);
}

void MainWindow::on_pushButtonLooterItemsEdit_clicked()
{
    if (!looterItemsTable->isSelectedEditable())
        return;

    const auto item = looterItemsTable->getSelectedForEdit();
    const auto categories = looterCategoriesTable->getCategories();

    const auto it = std::find_if(std::begin(categories), std::end(categories),
                                 [&item](const Amb::Ui::Module::Looter::Category &category)
                                 {
                                     return item.category == category.name;
                                 });

    bool setCombobox{ true };

    if (it == std::end(categories))
    {
        auto msg = QString("Category '%1' doesn't exist anymore.").arg(item.category.c_str());
        QMessageBox::information(this, "Error", msg, QMessageBox::Ok);
        setCombobox = false;
    }

    ui->editLooterItemsItem->setText(QString::fromStdString(item.name));

    if (setCombobox)
    {
        const auto idx = std::distance(std::begin(categories), it);
        ui->comboBoxLooterItemsCategories->setCurrentIndex(static_cast<int>(idx));
    }
}

void MainWindow::on_pushButtonLooterItemsClear_clicked()
{
    looterItemsTable->clear();
}

void MainWindow::on_pushButtonLooterItemsAdd_clicked()
{
    const auto itemName = ui->editLooterItemsItem->text().toStdString();

    if (!db.items.get(itemName).isValid())
    {
        auto msg = QString("Item '%1' doesn't exist.").arg(itemName.c_str());
        QMessageBox::information(this, "Error", msg, QMessageBox::Ok);
        return;
    }

    if (ui->comboBoxLooterItemsCategories->count() == 0)
    {
        QMessageBox::information(this, "Error", "Create at least one category in the 'Categories' tab.", QMessageBox::Ok);
        return;
    }

    if (looterItemsTable->itemExists(itemName))
    {
        auto msg = QString("Item '%1' is already on the list.").arg(itemName.c_str());
        QMessageBox::information(this, "Error", msg, QMessageBox::Ok);
        return;
    }

    const size_t categoryIdx = ui->comboBoxLooterItemsCategories->currentIndex();
    const auto category = looterCategoriesTable->getCategory(categoryIdx);
    const auto minCap = ui->spinBoxLooterItemsCapAbove->value();

    looterItemsTable->add({ itemName, category.name, std::to_string(minCap) });
}


void MainWindow::on_tabWidgetLooter_currentChanged(int index)
{
    const size_t LooterItemsTabIdx = 1;

    if (index == LooterItemsTabIdx)
    {
        ui->comboBoxLooterItemsCategories->clear();

        const auto categories = looterCategoriesTable->getCategories();
        for (const auto &cat : categories)
            ui->comboBoxLooterItemsCategories->addItem(QString::fromStdString(cat.name));
    }
}

void MainWindow::toggleLooter()
{
#ifdef AMB_PRO_COMPILATION
    if (!ui->checkBoxLooterRunning->isChecked())
    {
        stopModule(ui->checkBoxHealerRun,
                   Amb::Module::ModuleId::MOD_LOOTER);
    }
    else
    {
        if (!startModule(ui->checkBoxLooterRunning,
            Amb::Module::ModuleId::MOD_LOOTER))
        {
            ui->checkBoxHealerRun->setChecked(false);
        }
    }
#endif
}

void MainWindow::on_checkBoxLooterRunning_clicked()
{
    toggleLooter();
}

void MainWindow::setEnableDebugLogObserver(std::function<void(bool)> observer)
{
    enableDebugLogObserver = observer;
}


void MainWindow::on_actionEnable_debug_logs_toggled(bool checked)
{
    enableDebugLogObserver(checked);
}

void MainWindow::on_actionHide_nick_toggled(bool checked)
{
    updateTibiaClientsComboBox();
    const auto title = clientComboboxUpdater.getCurrent(checked);
    tibiaWindowChangedHandler(Amb::Utils::stringToWstring(title));
}

void MainWindow::on_actionShow_console_toggled(bool checked)
{
    //todo
    //if(checked)
        
}

void MainWindow::on_checkBoxMlvlRunning_toggled(bool checked)
{

}
