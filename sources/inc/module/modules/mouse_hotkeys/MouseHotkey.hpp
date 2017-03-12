#pragma once

#include "module/modules/mouse_hotkeys/MonitorableMouseEvent.hpp"
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
                    boost::property_tree::ptree toPropertyTree() const;
                    static MouseHotkey fromPtree(const boost::property_tree::ptree& tree);

                    MonitorableMouseEvent mouseEvent;
                    Client::Hotkey hotkey;
                    bool onlyWhenTibiaOnTop;
                };
            }
        }
    }
}
