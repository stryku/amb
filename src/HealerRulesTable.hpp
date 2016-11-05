#ifndef HEALERRULESTABLE_HPP
#define HEALERRULESTABLE_HPP

#include "HealRule.hpp"
#include "utils.hpp"

#include <QTableView>
#include <QStandardItemModel>
#include <QList>

class HealerRulesTable
{
public:
    HealerRulesTable( QTableView *view );

    void add( size_t minHp,
              size_t maxHp,
              size_t minMana,
              size_t maxMana,
              size_t size_tHotkey );

    void resetTableHeaders();

    void clear();

    std::vector<AMB::Modules::Heal::HealRule> getRules() const
    {
       int rowCount = model->rowCount();
       std::vector<AMB::Modules::Heal::HealRule> rules;

       for( int i = 0; i < rowCount; ++i )
            rules.push_back( getRule( i ) );

       return rules;
    }

private:
    void createModel();

    size_t getUInt( int row, int column ) const
    {
        auto item = model->item( row, column );
        return item->data(0).toUInt();
    }

    QString getQString( int row, int column ) const
    {
        auto item = model->item( row, column );
        return item->data(0).toString();
    }

    AMB::Utils::Hotkey getHotkey( int row ) const
    {
        auto stringHotkey = getQString( row, hotkeyColumnIndex );
        auto uintHot = stringHotkey.remove( 0, 1 ).toUInt() - 1;

        return AMB::Utils::size_tToHotkey( uintHot );
    }

    AMB::Modules::Heal::HealRule getRule( int row ) const
    {
        size_t minHp;
        size_t maxHp;
        size_t minMana;
        size_t maxMana;
        AMB::Utils::Hotkey hotkey;

        auto item = model->item( row, minHpColumnIndex );
        minHp = item->data().toUInt();

        minHp = getUInt( row, minHpColumnIndex );
        maxHp = getUInt( row, maxHpColumnIndex );
        minMana = getUInt( row, minManaColumnIndex );
        maxMana = getUInt( row, maxManaColumnIndex );

        hotkey = getHotkey( row );

        return { minHp, maxHp, minMana, maxMana, hotkey };
    }

private:
    typedef AMB::Modules::Heal::HealRule HealRule;

    static const size_t minHpColumnIndex = 0;
    static const size_t maxHpColumnIndex = 1;
    static const size_t minManaColumnIndex = 2;
    static const size_t maxManaColumnIndex = 3;
    static const size_t hotkeyColumnIndex = 4;

    QTableView *view;
    QStandardItemModel *model;
};

#endif // HEALERRULESTABLE_HPP
