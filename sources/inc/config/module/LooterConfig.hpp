#pragma once

#include <boost/property_tree/ptree.hpp>

#include <vector>

namespace Amb
{
    namespace Ui
    {
        namespace Module
        {
            namespace Looter
            {
                struct Category;
                struct LootItem;
            }
        }
    }

    namespace Config
    {
        namespace Module
        {
            struct LooterConfig
            {
                std::vector<Amb::Ui::Module::Looter::Category> categories;
                std::vector<Amb::Ui::Module::Looter::LootItem> items;

                Amb::Ui::Module::Looter::Category findCategory(const std::string &categoryName) const;
                boost::property_tree::ptree toPtree() const;
                static LooterConfig fromPtree(boost::property_tree::ptree &tree);
            };
        }
    }
}
