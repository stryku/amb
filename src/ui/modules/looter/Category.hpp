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
                             const std::string &strToOnto,
                             const std::string &destination)
                        : name{ name }
                        , toOnto{ ToOnto::fromString(strToOnto.c_str()) }
                        , destination{ destination }
                    {}

                    std::string name;
                    ToOnto::Type toOnto{ ToOnto::To };
                    std::string destination;
                };
            }
        }
    }
}
