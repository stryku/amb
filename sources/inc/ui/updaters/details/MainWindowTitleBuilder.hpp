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
                    MainWindowTitleBuilder& withCharacterName(const std::string &charName);
                    MainWindowTitleBuilder& withScriptName(const std::string &script);
                    MainWindowTitleBuilder& withHideNick(bool hide);
                    std::string build() const;

                private:
                    std::string characterName;
                    std::string scriptName;
                    constexpr static auto version = AMB_VERSION;
                    constexpr static auto name = "AMB";
                    bool hideNick{ false };
                };
            }
        }
    }
}
