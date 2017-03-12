#include "config/module/MouseHotkeysConfig.hpp"
#include "utils/PropertyTreeBuilder.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            boost::property_tree::ptree MouseHotkeysConfig::toPtree(const std::string& path) const
            {
                Utils::PropertyTreeBuilder builder;

                if (mouseHotkeys.empty())
                {
                    builder.addElement(Utils::PtreeElement<>{path + ".mouse_hotkeys", ""});
                    return builder.buildTree();
                }

                for (const auto& hot : mouseHotkeys)
                    builder.addTree(path + ".mouse_hotkeys.mouse_hotkey", hot.toPropertyTree());

                return builder.buildTree();
            }

            MouseHotkeysConfig MouseHotkeysConfig::fromPtree(const boost::property_tree::ptree& tree)
            {
                MouseHotkeysConfig mouseHotkeys;

                for (auto &child : tree.get_child("mouse_hotkeys"))
                {
                    const auto hot = Amb::Module::Modules::MouseHotkeys::MouseHotkey::fromPtree(child.second);
                    mouseHotkeys.mouseHotkeys.emplace_back(hot);
                }

                return mouseHotkeys;
            }
        }
    }
}
