#pragma once

#include "module/modules/mouse_hotkeys/MouseHotkey.hpp"

#include <boost/property_tree/ptree.hpp>

#include <vector>

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            struct MouseHotkeysConfig
            {
                std::vector<Amb::Module::Modules::MouseHotkeys::MouseHotkey> mouseHotkeys;

                boost::property_tree::ptree toPtree(const std::string& path = "") const;
                static MouseHotkeysConfig fromPtree(const boost::property_tree::ptree& tree);
            };
        }
    }
}
