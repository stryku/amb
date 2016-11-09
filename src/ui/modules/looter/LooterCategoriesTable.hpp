#pragma once

#include "ui/controls/Table.hpp"
#include "ui/modules/looter/Category.hpp"

namespace AMB
{
    namespace Ui
    {
        namespace Modules
        {
            namespace Looter
            {
                class LooterCategoriesTable
                {
                public:
                    LooterCategoriesTable(QTableView *view)
                        : table(view, { "Name", "To/Onto", "Destination" })
                    {}

                    std::vector<Category> getCategories() const
                    {
                        return table.getAll<Category>();
                    }

                    Category getCategory(const size_t row) const
                    {
                        return table.getItem<Category>(row);
                    }

                    bool isSelectedEditable() const
                    {
                        return table.selectedRows().size() == 1;
                    }

                    Category getSelectedCategoryForEdit() const
                    {
                        const auto rows = table.selectedRows();

                        if (rows.empty())
                            return{};

                        return table.getAndRemoveItem<Category>(rows[0]);
                    }

                    void add(const Category &category)
                    {
                        table.add(category.name, 
                                  ToOnto::toString(category.toOnto),
                                  category.destination);
                    }

                    void set(const const Category &category, size_t row)
                    {
                        table.set(row,
                                  category.name,
                                  ToOnto::toString(category.toOnto),
                                  category.destination);
                    }

                    bool categoryExists(const std::string &name) const
                    {
                        auto items = getCategories();

                        return std::find_if(std::begin(items), std::end(items),
                                            [&name](const Category &c)
                                            {
                                                return c.name == name;
                                            }) != std::end(items);
                    }

                    void clear()
                    {
                        table.clear();
                    }

                private:
                    static const size_t NumberOfColumns = 3;

                    AMB::Ui::Controls::Table<NumberOfColumns> table;
                };
            }
        }
    }
}
