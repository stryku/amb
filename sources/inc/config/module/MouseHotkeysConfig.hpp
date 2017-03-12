#pragma once

#include <boost/property_tree/ptree.hpp>

#include <vector>

namespace Amb
{
    namespace Module
    {
        namespace Modules
        {
            namespace MouseHotkeys
            {
                struct MouseHotkey;
            }
        }
    }

    namespace Config
    {
        namespace Module
        {
            struct MouseHotkeysConfig
            {
                std::vector<Amb::Module::Modules::MouseHotkeys::MouseHotkey> mouseHotkeys;

                boost::property_tree::ptree toPtree(const std::string& path = "") const;
                MouseHotkeysConfig fromPtree(const boost::property_tree::ptree& tree);
            };
        }
    }
}
