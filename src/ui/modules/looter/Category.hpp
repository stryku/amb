#pragma once

#include "ui/modules/looter/ToOnto.hpp"

#include <string>

namespace AMB
{
    namespace Ui
    {
        namespace Modules
        {
            namespace Looter
            {
                struct Category
                {
                    Category() = default;
                    Category(const std::string &name,
                             const std::string &destination,
                             const std::string &strToOnto)
                        : name{ name }
                        , destination{ destination }
                        , toOnto{ ToOnto::fromString(strToOnto.c_str()) }
                    {}

                    std::string name;
                    std::string destination;
                    ToOnto::Type toOnto;
                };
            }
        }
    }
}
