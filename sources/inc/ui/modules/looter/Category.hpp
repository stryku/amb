#pragma once

#include "ui/modules/looter/ToOnto.hpp"

#include <string>

namespace AMB
{
    namespace Ui
    {
        namespace Modules
        {
            namespace Looter
            {
                struct Category
                {
                    Category() = default;
                    Category(const std::string &name,
                             const std::string &strToOnto,
                             const std::string &destination)
                        : name{ name }
                        , toOnto{ ToOnto::fromString(strToOnto.c_str()) }
                        , destination{ destination }
                    {}

                    auto toPtree() const
                    {
                        Utils::PropertyTreeBuilder builder;

                        const auto elements =
                        {
                            Utils::PtreeElement<>{ "name", name },
                            Utils::PtreeElement<>{ "to_onto", ToOnto::toString(toOnto) },
                            Utils::PtreeElement<>{ "destination", destination },
                        };

                        return builder.addElements(elements).buildTree();
                    }

                    static Category fromPtree(boost::property_tree::ptree &tree)
                    {
                        Category category;

                        category.name = tree.get_child("name").get_value<std::string>();
                        category.destination = tree.get_child("destination").get_value<std::string>();
                        category.toOnto = ToOnto::fromString(tree.get_child("to_onto").get_value<std::string>());

                        return category;
                    }

                    std::string name;
                    ToOnto::Type toOnto{ ToOnto::To };
                    std::string destination;
                };
            }
        }
    }
}
