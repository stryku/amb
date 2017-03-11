#pragma once

#include "utils/Structs.hpp"
#include "capture/CaptureMode.hpp"
#include "client/TibiaClientType.hpp"

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            struct AdvancedSettingsConfig
            {
                struct
                {
                    FromTo randBetweenChecks;
                    FromTo sleepAfterHotkey;
                } healer;

                struct
                {
                    Capture::Mode captureMode;
                    Amb::Client::TibiaClientType clientType;
                } common;

                void toPropertyTreeBuilder(Utils::PropertyTreeBuilder &builder, const std::string &path = "") const;

                static AdvancedSettingsConfig fromPtree(boost::property_tree::ptree &tree);
            };
        }
    }
}