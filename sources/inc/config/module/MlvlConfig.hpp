#pragma once

#include "utils.hpp"

#include <boost/property_tree/ptree.hpp>

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            struct MlvlConfig
            {
                boost::property_tree::ptree toPtree() const;
                static MlvlConfig fromPtree(boost::property_tree::ptree &tree);

                size_t manaPercentFrom;
                size_t manaPercentTo;
                Utils::Hotkey spellHotkey;
                Utils::Hotkey foodHotkey;
            };
        }
    }
}
