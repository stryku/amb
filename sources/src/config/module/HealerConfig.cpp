#include "config/module/HealerConfig.hpp"
#include "ui/modules/healer/HealRule.hpp"
#include "utils/PropertyTreeBuilder.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            void HealerConfig::toPropertyTreeBuilder(Utils::PropertyTreeBuilder &builder, const std::string &path) const
            {
                if (rules.empty())
                {
                    builder.addElement(Utils::PtreeElement<>{path + ".heal_rules", ""});
                    return;
                }

                for (const auto& rule : rules)
                    rule.toPropertyTreeBuilder(builder, path + ".heal_rules.heal_rule");
            }

            boost::property_tree::ptree HealerConfig::toPtree() const
            {
                Utils::PropertyTreeBuilder builder;

                if (rules.empty())
                    return builder.addElement(Utils::PtreeElement<>{"heal_rules", ""}).buildTree();

                for (const auto& rule : rules)
                {
                    auto tree = rule.toPtree();
                    builder.addTree("heal_rules.heal_rule", tree);
                }

                return builder.buildTree();
            }

            HealerConfig HealerConfig::fromPtree(boost::property_tree::ptree &tree)
            {
                HealerConfig healer;

                for (auto &child : tree.get_child("heal_rules"))
                {
                    const auto rule = Amb::Module::Heal::HealRule::fromPtree(child.second);
                    healer.rules.emplace_back(rule);
                }

                return healer;
            }
        }
    }
}