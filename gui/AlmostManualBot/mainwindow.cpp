#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
