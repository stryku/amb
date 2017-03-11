#include "ui/modules/looter/Category.hpp"

#include "utils/PropertyTreeBuilder.hpp"

namespace Amb
{
    namespace Ui
    {
        namespace Module
        {
            namespace Looter
            {
                Category::Category(const std::string &name,
                                   const std::string &strToOnto,
                                   const std::string &destination)
                    : name{ name }
                    , toOnto{ ToOnto::fromString(strToOnto.c_str()) }
                    , destination{ destination }
                {}

                boost::property_tree::ptree Category::toPtree() const
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

                Category Category::fromPtree(boost::property_tree::ptree &tree)
                {
                    Category category;

                    category.name = tree.get_child("name").get_value<std::string>();
                    category.destination = tree.get_child("destination").get_value<std::string>();
                    category.toOnto = ToOnto::fromString(tree.get_child("to_onto").get_value<std::string>());

                    return category;
                }
            }
        }
    }
}
