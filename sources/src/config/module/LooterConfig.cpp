#include "config/module/LooterConfig.hpp"

#include "ui/modules/looter/Category.hpp"
#include "ui/modules/looter/LootItem.hpp"
#include "utils/PropertyTreeBuilder.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            Amb::Ui::Module::Looter::Category LooterConfig::findCategory(const std::string &categoryName) const
            {
                auto pred = [&categoryName](const auto &category)
                {
                    return category.name == categoryName;
                };

                const auto it = std::find_if(std::cbegin(categories),
                                             std::cend(categories),
                                             pred);

                BOOST_ASSERT_MSG(it != std::cend(categories), "Could not find category");

                return *it;
            }

            boost::property_tree::ptree LooterConfig::toPtree() const
            {
                Utils::PropertyTreeBuilder builder;

                if (categories.empty())
                    builder.addElement(Utils::PtreeElement<>{"categories", ""});
                else
                {
                    for (const auto& category : categories)
                    {
                        auto tree = category.toPtree();
                        builder.addTree("categories.category", tree);
                    }
                }

                if (items.empty())
                    builder.addElement(Utils::PtreeElement<>{"items", ""});
                else
                {
                    for (const auto& item : items)
                    {
                        auto tree = item.toPtree();
                        builder.addTree("items.item", tree);
                    }
                }

                return builder.buildTree();
            }

            LooterConfig LooterConfig::fromPtree(boost::property_tree::ptree &tree)
            {
                LooterConfig healer;

                for (auto &child : tree.get_child("categories"))
                {
                    const auto cat = Amb::Ui::Module::Looter::Category::fromPtree(child.second);
                    healer.categories.emplace_back(cat);
                }

                for (auto &child : tree.get_child("items"))
                {
                    const auto rule = Amb::Ui::Module::Looter::LootItem::fromPtree(child.second);
                    healer.items.emplace_back(rule);
                }

                return healer;
            }
        }
    }
}
