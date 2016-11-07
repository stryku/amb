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
                    constexpr static size_t To = 0;
                    constexpr static size_t Onto = 1;

                    constexpr static const char* toString(size_t v)
                    {
                        return
                            v == To ? "To" :
                            v == Onto ? "Onto" :
                            "UNDEF";
                    }

                    static size_t fromString(const std::string &str)
                    {
                        if (str == "To") return To;
                        if (str == "Onto") return Onto;
                        return -1;
                    }
                };
            }
        }
    }
}
