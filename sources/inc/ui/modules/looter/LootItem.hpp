#pragma once

#include <boost/property_tree/ptree.hpp>

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
                    LootItem() = default;
                    LootItem(const std::string &name, const std::string &category, const std::string& minCap);

                    bool isValid() const;
                    boost::property_tree::ptree toPtree() const;
                    static LootItem fromPtree(boost::property_tree::ptree &tree);

                    std::string name;
                    std::string category;
                    size_t minCap;
                };
            }
        }
    }
}
