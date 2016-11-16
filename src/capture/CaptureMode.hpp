#pragma once

#include "utils/PropertyTreeBuilder.hpp"

namespace AMB
{
    namespace Capture
    {
        struct Mode
        {
            enum class CaptureMode
            {
                OnlyCovered,
                OnlyNotCovered,
                Smart
            };

            CaptureMode mode{ CaptureMode::OnlyCovered };

            void fromSize_t(size_t val)
            {
                switch (val)
                {
                    case 0: mode = CaptureMode::OnlyCovered; break;
                    case 1: mode = CaptureMode::OnlyNotCovered; break;
                    case 2: mode = CaptureMode::Smart; break;
                }
            }

            size_t toSize_t() const
            {
                switch (mode)
                {
                    case AMB::Capture::Mode::CaptureMode::OnlyCovered: return 0;
                    case AMB::Capture::Mode::CaptureMode::OnlyNotCovered: return 1;
                    case AMB::Capture::Mode::CaptureMode::Smart: return 2;

                    default:
                        assert(false);
                }
            }

            void toPropertyTreeBuilder(Utils::PropertyTreeBuilder &builder, const std::string &path = "") const
            {
                std::string str;

                switch (mode)
                {
                    case AMB::Capture::Mode::CaptureMode::OnlyCovered: str = "OnlyCovered"; break;
                    case AMB::Capture::Mode::CaptureMode::OnlyNotCovered: str = "OnlyNotCovered"; break;
                    case AMB::Capture::Mode::CaptureMode::Smart: str = "Smart"; break;

                    default:
                        assert(false);
                }

                const auto elements =
                {
                    Utils::PtreeElement<>{ path + ".capture_mode", str }
                };

                builder.addElements(elements);
            }

            static Mode fromPtree(boost::property_tree::ptree &tree)
            {
                Mode ret;

                const auto str = tree.get<std::string>("capture_mode");

                if (str == "OnlyCovered") ret.mode = CaptureMode::OnlyCovered;
                else if (str == "OnlyNotCovered") ret.mode = CaptureMode::OnlyNotCovered;
                else if (str == "Smart") ret.mode = CaptureMode::Smart;

                return ret;
            }
        };
    }
}

