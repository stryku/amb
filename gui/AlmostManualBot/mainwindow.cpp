﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "utils.hpp"

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include <algorithm>

MainWindow::MainWindow(const AMB::Db::Database &db, QWidget *parent)
    : QMainWindow(parent)
    , ui{ new Ui::MainWindow }
    , db{ db }
{
    ui->setupUi(this);

    healerRulesTable = std::make_unique<AMB::Ui::Modules::Healer::HealerRulesTable>(ui->tableHealerRules);
    looterCategoriesTable = std::make_unique<AMB::Ui::Modules::Looter::LooterCategoriesTable>(ui->tableViewLooterCategoriesCategoriesList);
    looterItemsTable = std::make_unique<AMB::Ui::Modules::Looter::LooterItemsTable>(ui->tableLooterItems);
    
    updateTibiaClientsComboBox();
    QStringList strList;

    strList.reserve(db.items.size());

    for (const auto &item : db.items.getNames())
        strList << QString::fromStdString(item);

    itemsCompleter = new QCompleter(strList, this);
    itemsCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->editLooterItemsItem->setCompleter(itemsCompleter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTibiaClientsComboBox()
{
    auto clientsTitles = AMB::Utils::TibiaFinder::findAllClientsTitles();
    auto comboBox = ui->cbTibiaClients;

    comboBox->clear();

    comboBox->addItem( "Select client" );
    comboBox->addItem( "-------------" );

    for( auto &clientTitle : clientsTitles )
        comboBox->addItem( QString::fromStdWString( clientTitle ) );
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
                    AMB::Modules::ModuleId::MOD_HEALER );
    }
    else
    {
        if (!startModule(ui->checkBoxHealerRun,
                         AMB::Modules::ModuleId::MOD_HEALER))
        {
            ui->checkBoxHealerRun->setChecked(false);
        }
    }
}

bool MainWindow::startModule( QCheckBox *moduleCheckBox,
                              AMB::Modules::ModuleId modId )
{
    if (moduleToggleHandler(modId))
    {
        auto p = moduleCheckBox->palette();

        p.setColor(QPalette::Active, QPalette::WindowText, QColor("green"));
        moduleCheckBox->setPalette(p);
        moduleCheckBox->setText("Running");
        return true;
    }

    return false;
}

void MainWindow::stopModule( QCheckBox *moduleCheckBox,
                             AMB::Modules::ModuleId modId )
{
    auto p = moduleCheckBox->palette();

    p.setColor( QPalette::Active, QPalette::WindowText, QColor( "red" ) );
    moduleCheckBox->setPalette( p );
    moduleCheckBox->setText( "Not Running" );

    moduleToggleHandler( modId );
}

const Ui::MainWindow* MainWindow::getUi() const
{
    return ui;
}

AMB::Ui::Controls::AdvancedSettings::Healer MainWindow::getAdvancedSettingsHealer() const
{
    AMB::Ui::Controls::AdvancedSettings::Healer healer;

    healer.betweenChecks.from = ui->editRandBeetwenChecksFrom;
    healer.betweenChecks.to = ui->editRandBeetwenChecksTo;

    healer.sleepAfterHotkey.from = ui->editSleepAfterHotkeyFrom;
    healer.sleepAfterHotkey.to = ui->editSleepAfterHotkeyTo;

    return healer;
}

AMB::Ui::Controls::AdvancedSettings MainWindow::getAdvancedSettings() const
{
    AMB::Ui::Controls::AdvancedSettings controls;

    controls.healer = getAdvancedSettingsHealer();

    return controls;
}


AMB::Ui::Controls::Healer MainWindow::getHealer() const
{
    AMB::Ui::Controls::Healer healer;

    healer.healerRulesTable = healerRulesTable.get();

    return healer;
}

AMB::Ui::Controls::GlobalControls MainWindow::getControls() const
{
    AMB::Ui::Controls::GlobalControls controls;

    controls.healer = getHealer();
    controls.advancedSettings = getAdvancedSettings();

    return controls;
}


const AMB::Ui::Modules::Healer::HealerRulesTable& MainWindow::getHealerRulesTable() const
{
    return *( healerRulesTable.get() );
}

void MainWindow::setModuleToggleHandler( std::function<bool( AMB::Modules::ModuleId )> newHandler )
{
    moduleToggleHandler = newHandler;
}


void MainWindow::setTtibiaWindowChangedHandler( std::function<void(const std::wstring&)> newHandler )
{
    tibiaWindowChangedHandler = newHandler;
}

void MainWindow::setRefreshLayoutHandler(std::function<void()> newHandler)
{
    refreshLayoutHandler = newHandler;
}

void MainWindow::setConfigProvider(std::function<std::string()> provider)
{
    configToSaveProvider = provider;
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
        qDebug()<<"Catch std::bad_function_call: " << e.what();
    }
    catch( std::exception &e )
    {
        qDebug()<<"Catch std::exception: "<<e.what();
    }
}


void MainWindow::on_refreshLayoutButton_clicked()
{
    refreshLayoutHandler();
}

void MainWindow::on_actionOpen_triggered()
{
    auto path = QFileDialog::getOpenFileName(this, 
                                             "Open file", 
                                             { "./configurations" }, 
                                             "*.amb");

    if (!path.length() == 0)
    {
        auto fileContent = AMB::Utils::readWholeFileIntoString(path.toStdString());
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
        std::ofstream out(path.toStdString());
        if (out.is_open())
            out << config;
    }
}

void MainWindow::on_actionSave_triggered()
{
    auto path = QFileDialog::getExistingDirectory(this,
                                                  "Save file",
                                                  "./configurations");

    if (!path.length() == 0)
    {
        const auto config = configToSaveProvider();
        std::ofstream out(path.toStdString());
        if (out.is_open())
            out << config;
    }
}

void MainWindow::on_pushButtonLooterCategoriesNewCategoryAdd_clicked()
{
    AMB::Ui::Modules::Looter::Category category;

    auto name = ui->editLooterCategoriesNewCategorName->text();

    if (looterCategoriesTable->categoryExists(name.toStdString()))
    {
        auto msg = QString("Category '%1' already exist.").arg(name);
        QMessageBox::information(this, "Error", msg, QMessageBox::Ok);
        return;
    }

    category.name = name.toStdString();
    category.destination = ui->editLooterCategoriesNewCategoryDestination->text().toStdString();
    category.toOnto = ui->comboBoxLooterCategoriesToOnto->currentIndex();

    looterCategoriesTable->add(category);

    ui->comboBoxLooterItemsCategories->clear();

    const auto categories = looterCategoriesTable->getCategories();
    for (const auto &cat : categories)
        ui->comboBoxLooterItemsCategories->addItem(QString::fromStdString(cat.name));
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
        ui->cbHealerHotkey->setCurrentIndex(static_cast<int>(AMB::Utils::hotkeyToSize_t(rule.hotkey)));
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
                                 [&item](const AMB::Ui::Modules::Looter::Category &category)
                                 {
                                     return item.category == category.name;
                                 });

    bool setCombobox{ true };

    if (it == std::end(categories))
    {
        auto msg = QString("Category '%1' doesn't exist anymore.").arg(item.name.c_str());
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

    const size_t categoryIdx = ui->comboBoxLooterItemsCategories->currentIndex();
    const auto category = looterCategoriesTable->getCategory(categoryIdx);

    looterItemsTable->add({ itemName, category.name });
}
