#include "module/modules/mouse_hotkeys/MouseHotkey.hpp"
#include "utils/PropertyTreeBuilder.hpp"
#include "utils/string/fromString.hpp"

namespace Paths
{
    const auto kFirstEvent = "events.first";
    const auto kSecondEvent = "events.second";
    const auto kHotkey = "hotkey";
    const auto kOnlyIfOnTop = "only_if_on_top";
}

namespace Amb
{
    namespace Module
    {
        namespace Modules
        {
            namespace MouseHotkeys
            {
                boost::property_tree::ptree MouseHotkey::toPropertyTree() const
                {
                    Utils::PropertyTreeBuilder builder;

                    const auto elements =
                    {
                        Utils::PtreeElement<>{ Paths::kFirstEvent, utils::toString(mouseEvent.first) },
                        Utils::PtreeElement<>{ Paths::kSecondEvent, utils::toString(mouseEvent.first) },
                        Utils::PtreeElement<>{ Paths::kHotkey, Client::hotkeyToStdString(hotkey) },
                        Utils::PtreeElement<>{ Paths::kOnlyIfOnTop, utils::toString(onlyWhenTibiaOnTop) },
                    };

                    return builder.addElements(elements).buildTree();
                }


                MouseHotkey MouseHotkey::fromPtree(const boost::property_tree::ptree& tree)
                {
                    MouseHotkey hot;

                    hot.mouseEvent.first = tree.get_child(Paths::kFirstEvent).get_value<size_t>();
                    hot.mouseEvent.second = tree.get_child(Paths::kSecondEvent).get_value<size_t>();

                    const auto strBool = tree.get_child(Paths::kOnlyIfOnTop).get_value<std::string>();
                    hot.onlyWhenTibiaOnTop = Utils::String::fromString(strBool);

                    auto strhot = tree.get_child(Paths::kHotkey).get_value<std::string>();
                    hot.hotkey = Client::stdStringToHotkey(strhot);

                    return hot;
                }
            }
        }
    }
}
