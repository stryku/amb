#pragma once

#include <boost/property_tree/ptree.hpp>

#include <vector>

namespace Amb
{
    namespace Utils
    {
        class PropertyTreeBuilder;
    }

    namespace Module
    {
        namespace Heal
        {
            struct HealRule;
        }
    }

    namespace Config
    {
        namespace Module
        {
            struct HealerConfig
            {
                void toPropertyTreeBuilder(Utils::PropertyTreeBuilder &builder, const std::string &path = "") const;
                auto toPtree() const;
                static HealerConfig fromPtree(boost::property_tree::ptree &tree);

                std::vector<Amb::Module::Heal::HealRule> rules;
            };
        }
    }
}