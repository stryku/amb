#include "HealerRulesTable.hpp"

HealerRulesTable::HealerRulesTable( QTableView *view ) :
    view( view )
{
    createModel();
}

void HealerRulesTable::createModel()
{
    QStandardItemModel *newModel = new QStandardItemModel( 0, 0 );

    newModel->setHorizontalHeaderItem( minHpColumnIndex, new QStandardItem( QString( "Min HP" ) ) );
    newModel->setHorizontalHeaderItem( maxHpColumnIndex, new QStandardItem( QString( "Max HP" ) ) );
    newModel->setHorizontalHeaderItem( minManaColumnIndex, new QStandardItem( QString( "Min Mana" ) ) );
    newModel->setHorizontalHeaderItem( maxManaColumnIndex, new QStandardItem( QString( "Max Mana" ) ) );
    newModel->setHorizontalHeaderItem( hotkeyColumnIndex, new QStandardItem( QString( "Hotkey" ) ) );

    view->setModel( newModel );
    model = newModel;
}



static const size_t minHpColumnIndex = 0;
static const size_t maxHpColumnIndex = 1;
static const size_t minManaColumnIndex = 2;
static const size_t maxManaColumnIndex = 3;
static const size_t hotkeyColumnIndex = 4;

void HealerRulesTable::add( size_t minHp,
                            size_t maxHp,
                            size_t minMana,
                            size_t maxMana,
                            size_t size_tHotkey )
{
    auto rowCount = model->rowCount();

    model->appendRow( new QStandardItem() );

    model->setItem( rowCount,
                    minHpColumnIndex,
                    new QStandardItem( QString::number( minHp ) ) );

    model->setItem( rowCount,
                    maxHpColumnIndex,
                    new QStandardItem( QString::number( maxHp ) ) );

    model->setItem( rowCount,
                    minManaColumnIndex,
                    new QStandardItem( QString::number( minMana ) ) );

    model->setItem( rowCount,
                    maxManaColumnIndex,
                    new QStandardItem( QString::number( maxMana ) ) );

    auto strHotkey = AMB::Utils::size_tHotkeyToStdString( size_tHotkey );

    model->setItem( rowCount,
                    hotkeyColumnIndex,
                    new QStandardItem( QString::fromStdString( strHotkey ) ) );

    view->resizeColumnsToContents();
}

void HealerRulesTable::clear()
{
    model->clear();
}
