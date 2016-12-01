#include "ui/updaters/details/MainWindowTitleBuilder.hpp"

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            namespace details
            {
                MainWindowTitleBuilder& MainWindowTitleBuilder::withCharacterName(const std::string &charName)
                {
                    characterName = charName;
                    return *this;
                }

                MainWindowTitleBuilder& MainWindowTitleBuilder::withScriptName(const std::string &script)
                {
                    scriptName = script;
                    return *this;
                }

                std::string MainWindowTitleBuilder::build() const
                {
                    std::string ret{ name };

                    ret += std::string{ version };
                    
                    if(!characterName.empty())
                        ret += " - " + characterName;

                    if (!scriptName.empty())
                        ret += " (" + scriptName + ")";

                    return ret;
                }
            };
        }
    }
}
