#pragma once

#include "ui/controls/Table.hpp"
#include "ui/modules/healer/HealRule.hpp"

namespace AMB
{
    namespace Ui
    {
        namespace Modules
        {
            namespace Healer
            {
                class HealerRulesTable
                {
                private:
                    using HealRule = AMB::Modules::Heal::HealRule;

                public:
                    HealerRulesTable(QTableView *view)
                        : table(view, { "Min hp", "Max hp", "Min mana", "Max mana", "Hotkey"})
                    {}

                    std::vector<HealRule> getRules() const
                    {
                        return table.getItems<HealRule>();
                    }

                    HealRule get(const size_t row) const
                    {
                        return table.getItem<HealRule>(row);
                    }

                    bool isSelectedEditable() const
                    {
                        return table.selectedRows().size() == 1;
                    }

                    HealRule getSelectedForEdit() const
                    {
                        const auto rows = table.selectedRows();

                        if (rows.empty())
                            return{};

                        return table.getAndRemoveItem<HealRule>(rows[0]);
                    }

                    void add(const HealRule &rule)
                    {
                        table.add(utils::toString(rule.minHp),
                                  utils::toString(rule.maxHp),
                                  utils::toString(rule.minMana),
                                  utils::toString(rule.maxMana),
                                  Utils::hotkeyToStdString(rule.hotkey));
                    }

                    void add(size_t minHp, size_t maxHp, size_t minMana, size_t maxMana, size_t hotkey)
                    {
                        auto hot = Utils::size_tToHotkey(hotkey);

                        add(HealRule{ minHp,maxHp, minMana,maxMana, hot });
                    }

                    void set(const HealRule &rule, size_t row)
                    {
                        table.set(row,
                                  utils::toString(rule.minHp),
                                  utils::toString(rule.maxHp),
                                  utils::toString(rule.minMana),
                                  utils::toString(rule.maxMana),
                                  Utils::hotkeyToStdString(rule.hotkey));
                    }

                    void clear()
                    {
                        table.clear();
                    }

                private:
                    static const size_t NumberOfColumns = 5;

                    AMB::Ui::Controls::Table<NumberOfColumns> table;
                };
            }
        }
    }
}
