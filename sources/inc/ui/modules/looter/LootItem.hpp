#pragma once

#include "ui/modules/looter/Category.hpp"

#include <string>

namespace Amb
{
    namespace Ui
    {
        namespace Module
        {
            namespace Looter
            {
                struct LootItem
                {
                    std::string name;
                    std::string category;
                    size_t minCap;

                    LootItem() = default;

                    LootItem(const std::string &name, const std::string &category, const std::string& minCap)
                        : name{ name }
                        , category{ category }
                        , minCap{ static_cast<size_t>(std::stoul(minCap)) }
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
                            Utils::PtreeElement<>{ "min_cap", std::to_string(minCap) }
                        };

                        return builder.addElements(elements).buildTree();
                    }

                    static LootItem fromPtree(boost::property_tree::ptree &tree)
                    {
                        LootItem item;

                        item.name = tree.get_child("name").get_value<std::string>();
                        item.category = tree.get_child("category").get_value<std::string>();
                        item.minCap = tree.get_child("min_cap").get_value<size_t>();

                        return item;
                    }
                };
            }
        }
    }
}
