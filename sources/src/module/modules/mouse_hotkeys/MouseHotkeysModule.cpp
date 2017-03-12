#include "module/modules/mouse_hotkeys/MouseHotkeysModule.hpp"
#include "config/module/MouseHotkeysConfig.hpp"

namespace Amb
{
    namespace Module
    {
        namespace Modules
        {
            namespace MouseHotkeys
            {
                MouseHotkeysModule::MouseHotkeysModule(Simulate::Simulator &simulator,
                                                       const Client::TibiaClientWindowInfo &tibiaClientWindowInfo,
                                                       const Config::Module::MouseHotkeysConfig& mouseHotkeysConfig)
                    : ModuleCore(simulator, tibiaClientWindowInfo)
                    , mouseHotkeysConfig{ mouseHotkeysConfig }
                {}

                void MouseHotkeysModule::runDetails()
                {
                    std::this_thread::sleep_for(std::chrono::seconds{ 1 });
                }

                void MouseHotkeysModule::applyConfigs()
                {

                }
            }
        }
    }
}
