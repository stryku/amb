#include "HealerRulesTable.hpp"

HealerRulesTable::HealerRulesTable( QTableView *view ) :
    view( view )
{
    createModel();
}

void HealerRulesTable::resetTableHeaders()
{
    model->setHorizontalHeaderItem( minHpColumnIndex, new QStandardItem( QString( "Min HP" ) ) );
    model->setHorizontalHeaderItem( maxHpColumnIndex, new QStandardItem( QString( "Max HP" ) ) );
    model->setHorizontalHeaderItem( minManaColumnIndex, new QStandardItem( QString( "Min Mana" ) ) );
    model->setHorizontalHeaderItem( maxManaColumnIndex, new QStandardItem( QString( "Max Mana" ) ) );
    model->setHorizontalHeaderItem( hotkeyColumnIndex, new QStandardItem( QString( "Hotkey" ) ) );
}

void HealerRulesTable::createModel()
{
    model = new QStandardItemModel( 0, 0 );

    view->setModel( model );

    resetTableHeaders();
}



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
    resetTableHeaders();
}
