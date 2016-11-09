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

                    auto toPtree() const
                    {
                        Utils::PropertyTreeBuilder builder;

                        const auto elements =
                        {
                            Utils::PtreeElement<>{ "name", name },
                            Utils::PtreeElement<>{ "category", category },
                        };

                        return builder.addElements(elements).buildTree();
                    }

                    static LootItem fromPtree(boost::property_tree::ptree &tree)
                    {
                        LootItem item;

                        item.name = tree.get_child("name").get_value<std::string>();
                        item.category = tree.get_child("category").get_value<std::string>();

                        return item;
                    }
                };
            }
        }
    }
}
