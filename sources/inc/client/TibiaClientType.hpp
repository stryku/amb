#pragma once

#include "utils/PropertyTreeBuilder.hpp"

namespace Amb
{
    namespace Client
    {
        enum class TibiaClientType
        {
            Tibia10,
            Tibia11,
            Flash
        };

        void toPropertyTreeBuilder(Amb::Utils::PropertyTreeBuilder &builder, TibiaClientType type, const std::string &path = "");
        TibiaClientType fromPtree(boost::property_tree::ptree &tree);
        TibiaClientType fromSize_t(size_t val);
        size_t toSize_t(TibiaClientType type);
    }
}
