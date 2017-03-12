#include "module/modules/mouse_hotkeys/MouseHotkeysModule.hpp"
#include "config/module/MouseHotkeysConfig.hpp"
#include "monitor/mouse/MouseMonitorFactory.hpp"
#include "monitor/mouse/IMouseMonitor.hpp"

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
                                                       const Config::Module::MouseHotkeysConfig& mouseHotkeysConfig,
                                                       Monitor::Mouse::MouseMonitorFactory& mouseMonitorFactory)
                    : ModuleCore(simulator, tibiaClientWindowInfo)
                    , mouseHotkeysConfig{ mouseHotkeysConfig }
                    , mouseMonitor{ mouseMonitorFactory.create() }
                {
                    auto cb = [this](auto ev)
                    {
                        mouseEventCallback(ev);
                    };

                    mouseMonitor->setCallback(cb);
                }

                MouseHotkeysModule::~MouseHotkeysModule()
                {}

                void MouseHotkeysModule::runDetails()
                {
                }

                void MouseHotkeysModule::mouseEventCallback(Mouse::MouseEvent ev)
                {

                }

                void MouseHotkeysModule::run()
                {
                    mouseMonitor->start();
                    ModuleCore::run();
                }

                void MouseHotkeysModule::stop()
                {
                    mouseMonitor->stop();
                    ModuleCore::stop();
                }

                void MouseHotkeysModule::applyConfigs()
                {
                }
            }
        }
    }
}
