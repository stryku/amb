#include "module/modules/mouse_hotkeys/MouseHotkeysModule.hpp"
#include "config/module/MouseHotkeysConfig.hpp"
#include "monitor/mouse/MouseMonitorFactory.hpp"
#include "monitor/mouse/IMouseMonitor.hpp"
#include "log/log.hpp"

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

                boost::optional<Client::Hotkey> MouseHotkeysModule::getHotkeyForEvent(const Mouse::MouseEvent& ev) const
                {
                    const auto pred = [&ev](const auto& mouseHotkey)
                    {
                        return mouseHotkey.mouseEvent == ev;
                    };

                    const auto it = std::find_if(std::cbegin(mouseHotkeysConfig.mouseHotkeys),
                                                 std::cend(mouseHotkeysConfig.mouseHotkeys),
                                                 pred);

                    if (it == std::cend(mouseHotkeysConfig.mouseHotkeys))
                        return{};

                    return it->hotkey;
                }

                void MouseHotkeysModule::runDetails()
                {
                }

                void MouseHotkeysModule::mouseEventCallback(Mouse::MouseEvent ev)
                {
                    const auto optionalHot = getHotkeyForEvent(ev);

                    if (optionalHot)
                    {
                        LOG_DEBUG("MouseHotkeysModule::mouseEventCallback simulating hotkey: {}", Client::hotkeyToStdString(*optionalHot));
                        simulator.hotkey(*optionalHot);
                    }
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
