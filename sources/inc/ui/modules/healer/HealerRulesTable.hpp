#pragma once

#include "ui/controls/Table.hpp"
#include "ui/modules/healer/HealRule.hpp"

namespace Amb
{
    namespace Ui
    {
        namespace Module
        {
            namespace Healer
            {
                class HealerRulesTable : public Amb::Ui::Controls::Table<5>
                {
                private:
                    using HealRule = Amb::Module::Heal::HealRule;
                    using Table = Amb::Ui::Controls::Table<5>;

                public:
                    HealerRulesTable(QTableView *view)
                        : Table(view, { "Min hp", "Max hp", "Min mana", "Max mana", "Hotkey"})
                    {}

                    std::vector<HealRule> getRules() const
                    {
                        return getAll<HealRule>();
                    }

                    HealRule get(const size_t row) const
                    {
                        return getItem<HealRule>(row);
                    }

                    bool isSelectedEditable() const
                    {
                        return selectedRows().size() == 1;
                    }

                    HealRule getSelectedForEdit() const
                    {
                        const auto rows = selectedRows();

                        if (rows.empty())
                            return{};

                        return getAndRemoveItem<HealRule>(rows[0]);
                    }

                    void add(const HealRule &rule)
                    {
                        Table::add(utils::toString(rule.minHp),
                                   utils::toString(rule.maxHp),
                                   utils::toString(rule.minMana),
                                   utils::toString(rule.maxMana),
                                   Client::hotkeyToStdString(rule.hotkey));
                    }

                    void add(size_t minHp, size_t maxHp, size_t minMana, size_t maxMana, size_t hotkey)
                    {
                        auto hot = Client::size_tToHotkey(hotkey);

                        add(HealRule{ minHp,maxHp, minMana,maxMana, hot });
                    }

                    void set(const HealRule &rule, size_t row)
                    {
                        Table::set(row,
                                  utils::toString(rule.minHp),
                                  utils::toString(rule.maxHp),
                                  utils::toString(rule.minMana),
                                  utils::toString(rule.maxMana),
                                   Client::hotkeyToStdString(rule.hotkey));
                    }
                };
            }
        }
    }
}
