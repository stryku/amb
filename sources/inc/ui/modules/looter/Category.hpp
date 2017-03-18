#pragma once

#include "ui/modules/looter/ToOnto.hpp"

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
                struct Category
                {
                    Category() = default;
                    Category(const std::string &name,
                             const std::string &strToOnto,
                             const std::string &destination);

                    boost::property_tree::ptree toPtree() const;

                    static Category fromPtree(boost::property_tree::ptree &tree);

                    std::string name;
                    ToOnto::Type toOnto{ ToOnto::To };
                    std::string destination;
                };
            }
        }
    }
}
