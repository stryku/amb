#ifndef HEALERRULESTABLE_HPP
#define HEALERRULESTABLE_HPP

#include <HealRule.hpp>
#include <utils.hpp>

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

private:
    void createModel();

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
