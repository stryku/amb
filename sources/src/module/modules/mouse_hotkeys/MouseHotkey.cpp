#include "module/modules/mouse_hotkeys/MouseHotkey.hpp"
#include "utils/PropertyTreeBuilder.hpp"
#include "utils/string/fromString.hpp"

namespace Paths
{
    //const auto kFirstEvent = "events.first";
    const auto kMouseEvent = "mouse_event";
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
                MouseHotkey::MouseHotkey(const std::string& strMouseEvent,
                                         const std::string& strHot,
                                         const std::string& strBool)
                    : mouseEvent{ Mouse::MouseEvent::fromPrettyString(strMouseEvent) }
                    , hotkey{ Client::stdStringToHotkey(strHot) }
                    , onlyWhenTibiaOnTop{ Utils::String::fromString(strBool) }
                {}

                boost::property_tree::ptree MouseHotkey::toPropertyTree() const
                {
                    Utils::PropertyTreeBuilder builder;

                    const auto elements =
                    {
                        //Utils::PtreeElement<>{ Paths::kFirstEvent, utils::toString(mouseEvent.first) },
                        Utils::PtreeElement<>{ Paths::kMouseEvent, mouseEvent.toString() },
                        Utils::PtreeElement<>{ Paths::kHotkey, Client::hotkeyToStdString(hotkey) },
                        Utils::PtreeElement<>{ Paths::kOnlyIfOnTop, utils::toString(onlyWhenTibiaOnTop) },
                    };

                    return builder.addElements(elements).buildTree();
                }


                MouseHotkey MouseHotkey::fromPtree(const boost::property_tree::ptree& tree)
                {
                    MouseHotkey hot;

                    const auto strEv = tree.get_child(Paths::kMouseEvent).get_value<std::string>();
                    hot.mouseEvent = Amb::Mouse::MouseEvent::fromString(strEv);

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
