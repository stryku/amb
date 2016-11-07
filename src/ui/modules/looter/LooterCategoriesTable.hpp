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
                        return table.getItems<Category>();
                    }

                    void add(const Category &category)
                    {
                        const std::string toOntoStr = (category.toOnto == ToOnto::TO) ? "To" : "Onto";

                        table.add(category.name, 
                                  category.destination, 
                                  toOntoStr);
                    }

                private:
                    static const size_t NumberOfColumns = 3;

                    AMB::Ui::Controls::Table<NumberOfColumns> table;
                };
            }
        }
    }
}
