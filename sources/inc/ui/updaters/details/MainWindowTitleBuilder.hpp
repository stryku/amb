#pragma once

#include <string>

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            namespace details
            {
                class MainWindowTitleBuilder
                {
                public:



                private:
                    std::string characterName;
                    std::string scriptName;
                    constexpr static auto version = #AMB_VERSION;
                    constexpr static auto name = "AMB";
                };
            }
        }
    }
}
