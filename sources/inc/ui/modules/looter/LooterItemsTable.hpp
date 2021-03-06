#pragma once

#include "ui/controls/Table.hpp"
#include "ui/modules/looter/LootItem.hpp"
#include "db/Items.hpp"

namespace
{
    const size_t NumberOfTableColumns = 3;
}

namespace Amb
{
    namespace Ui
    {
        namespace Module
        {
            namespace Looter
            {
                class LooterItemsTable : public Amb::Ui::Controls::Table<NumberOfTableColumns>
                {
                private:
                    using ItemType = Amb::Ui::Module::Looter::LootItem;
                    using Table = Amb::Ui::Controls::Table<NumberOfTableColumns>;

                public:
                    LooterItemsTable(QTableView *view)
                        : Table(view, { "Item", "Category", "Min Cap" })
                    {}

                    std::vector<ItemType> getItems() const
                    {
                        return getAll<typename ItemType>();
                    }

                    ItemType get(const size_t row) const
                    {
                        return getItem<ItemType>(row);
                    }

                    bool isSelectedEditable() const
                    {
                        return selectedRows().size() == 1;
                    }

                    ItemType getSelectedForEdit() const
                    {
                        const auto rows = selectedRows();

                        if (rows.empty())
                            return{};

                        return getAndRemoveItem<ItemType>(rows[0]);
                    }

                    void add(const ItemType &item)
                    {
                        Table::add(item.name,
                                   item.category,
                                   std::to_string(item.minCap));
                    }

                    void add(const std::string &name, const Category &category, size_t minCap)
                    {
                        add(ItemType{ name, category.name, std::to_string(minCap) });
                    }

                    void set(const ItemType &item, size_t row)
                    {
                        Table::set(row,
                                   item.name,
                                   item.category,
                                   std::to_string(item.minCap));
                    }

                    bool itemExists(const std::string &name) const
                    {
                        auto items = getItems();

                        return std::find_if(std::begin(items), std::end(items),
                                            [&name](const LootItem &item)
                                            {
                                                return item.name == name;
                                            }) != std::end(items);
                    }
                };
            }
        }
    }
}