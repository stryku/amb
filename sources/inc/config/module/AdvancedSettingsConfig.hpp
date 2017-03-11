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
            struct AdvancedSettings
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

                static AdvancedSettings fromPtree(boost::property_tree::ptree &tree);
            };
        }
    }
}