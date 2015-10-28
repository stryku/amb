#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stopModule( ui->checkBoxHealerRun,
                AMB::Modules::ModuleId::MOD_HEALER );

    healerRulesTable = std::make_unique<HealerRulesTable>( ui->tableHealerRules );

    updateTibiaClientsComboBox();
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
    const auto minHealEdit = ui->editHealerMinHp;
    const auto maxHealEdit = ui->editHealerMaxHp;
    const auto minManaEdit = ui->editHealerMinMana;
    const auto maxManaEdit = ui->editHealerMaxMana;
    const auto hotkeyCombo = ui->cbHealerHotkey;

    size_t minHeal = minHealEdit->text().toUInt();
    size_t maxHeal = maxHealEdit->text().toUInt();
    size_t minMana = minManaEdit->text().toUInt();
    size_t maxMana = maxManaEdit->text().toUInt();

    auto hotkey = hotkeyCombo->currentIndex();

    healerRulesTable->add( minHeal,
                           maxHeal,
                           minMana,
                           maxMana,
                           hotkey );
}

void MainWindow::on_btnHealerClear_clicked()
{
    healerRulesTable->clear();
}

void MainWindow::toggleHealer()
{
    if( ui->checkBoxHealerRun->isChecked() )
    {
        stopModule( ui->checkBoxHealerRun,
                    AMB::Modules::ModuleId::MOD_HEALER );
    }
    else
    {
        startModule( ui->checkBoxHealerRun,
                     AMB::Modules::ModuleId::MOD_HEALER );
    }
}

void MainWindow::startModule( QCheckBox *moduleCheckBox,
                              AMB::Modules::ModuleId modId )
{
    auto p = moduleCheckBox->palette();

    p.setColor( QPalette::Active, QPalette::WindowText, QColor( "green" ) );
    moduleCheckBox->setPalette( p );
    moduleCheckBox->setText( "Running" );

    moduleToggleHandler( modId );
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

const HealerRulesTable& MainWindow::getHealerRulesTable() const
{
    return *( healerRulesTable.get() );
}

void MainWindow::setModuleToggleHandler( std::function<void( AMB::Modules::ModuleId )> newHandler )
{
    moduleToggleHandler = newHandler;
}

std::wstring MainWindow::getTibiaWindowTitle() const
{
    const auto cbTibiaClients = ui->cbTibiaClients;
    auto variant = cbTibiaClients->currentData();

    return variant.toString().toStdWString();
}
