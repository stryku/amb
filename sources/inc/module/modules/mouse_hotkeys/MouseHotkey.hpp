#pragma once

#include "mouse/MouseEvent.hpp"
#include "client/Hotkey.hpp"

#include <boost/property_tree/ptree.hpp>

namespace Amb
{
    namespace Module
    {
        namespace Modules
        {
            namespace MouseHotkeys
            {
                struct MouseHotkey
                {
                    MouseHotkey() = default;
                    MouseHotkey(const std::string& strMouseEvent,
                                const std::string& strHot,
                                const std::string& strOnlyWhenTibiaOnTop);

                    boost::property_tree::ptree toPropertyTree() const;
                    static MouseHotkey fromPtree(const boost::property_tree::ptree& tree);

                    Mouse::MouseEvent mouseEvent;
                    Client::Hotkey hotkey;
                    bool onlyWhenTibiaOnTop;
                };
            }
        }
    }
}
