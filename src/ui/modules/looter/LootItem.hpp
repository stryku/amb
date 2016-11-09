#pragma once

#include "ui/modules/looter/Category.hpp"

#include <string>

namespace AMB
{
    namespace Ui
    {
        namespace Modules
        {
            namespace Looter
            {
                struct LootItem
                {
                    std::string name;
                    std::string category;

                    LootItem() = default;

                    LootItem(const std::string &name, const std::string &category)
                        : name{ name }
                        , category{ category }
                    {}

                    bool isValid() const
                    {
                        return !name.empty();
                    }
                };
            }
        }
    }
}
