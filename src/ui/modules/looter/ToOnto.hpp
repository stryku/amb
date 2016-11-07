#pragma once

#include <string>

namespace AMB
{
    namespace Ui
    {
        namespace Modules
        {
            namespace Looter
            {
                struct ToOnto
                {
                    using Type = size_t;
                    constexpr static size_t TO = 0;
                    constexpr static size_t ONTO = 1;

                    constexpr static const char* toString(size_t v)
                    {
                        return
                            v == TO ? "TO" :
                            v == ONTO ? "ONTO" :
                            "UNDEF";
                    }

                    static size_t fromString(const std::string &str)
                    {
                        if (str == "TO") return TO;
                        if (str == "ONTO") return ONTO;
                        return -1;
                    }
                };
            }
        }
    }
}
