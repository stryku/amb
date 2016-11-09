#pragma once

#include "ui/controls/Table.hpp"
#include "ui/modules/looter/LootItem.hpp"
#include "db/Items.hpp"

namespace
{
    const size_t NumberOfTableColumns = 2;
}

namespace AMB
{
    namespace Ui
    {
        namespace Modules
        {
            namespace Looter
            {
                class LooterItemsTable : public AMB::Ui::Controls::Table<NumberOfTableColumns>
                {
                private:
                    using ItemType = AMB::Ui::Modules::Looter::LootItem;
                    using Table = AMB::Ui::Controls::Table<NumberOfTableColumns>;

                public:
                    LooterItemsTable(QTableView *view)
                        : Table(view, { "Item", "Category" })
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
                                   item.category);
                    }

                    void add(const std::string &name, const Category &category)
                    {
                        add(ItemType{ name, category.name });
                    }

                    void set(const ItemType &item, size_t row)
                    {
                        Table::set(row,
                                   item.name,
                                   item.category);
                    }
                };
            }
        }
    }
}