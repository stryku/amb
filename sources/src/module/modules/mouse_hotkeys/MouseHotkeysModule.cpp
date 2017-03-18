#include "module/modules/mouse_hotkeys/MouseHotkeysModule.hpp"
#include "config/module/MouseHotkeysConfig.hpp"
#include "config/GlobalConfig.hpp"
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
                                                       const Config::GlobalConfig& globalConfig,
                                                       const Config::Module::MouseHotkeysConfig& mouseHotkeysConfig,
                                                       Monitor::Mouse::MouseMonitorFactory& mouseMonitorFactory)
                    : ModuleCore(simulator, tibiaClientWindowInfo)
                    , mouseHotkeysConfig{ mouseHotkeysConfig }
                    , globalConfig{ globalConfig }
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

                void MouseHotkeysModule::attachToNewProcess(DWORD pid)
                {
                    currentTibiaPid = pid;
                }


                boost::optional<MouseHotkey> MouseHotkeysModule::getHotkeyForEvent(const Mouse::MouseEvent& ev) const
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

                    return *it;
                }

                void MouseHotkeysModule::runDetails()
                {
                    asyncTaskManager.tick();
                    std::this_thread::sleep_for(std::chrono::milliseconds{ 50 });
                }

                bool MouseHotkeysModule::tibiaIsOnTop()
                {
                    DWORD pid;
                    GetWindowThreadProcessId(GetForegroundWindow(), &pid);
                    return currentTibiaPid == pid;
                }

                void MouseHotkeysModule::mouseEventCallback(Mouse::MouseEvent ev)
                {
                    const auto optionalHot = getHotkeyForEvent(ev);

                    if (optionalHot)
                    {
                        if ((optionalHot->onlyWhenTibiaOnTop && tibiaIsOnTop()) ||
                            !optionalHot->onlyWhenTibiaOnTop)
                        {
                            LOG_DEBUG("MouseHotkeysModule::mouseEventCallback Adding hotkey to async tasks: {}", Client::hotkeyToStdString(optionalHot->hotkey));
                            const auto kDelay = std::chrono::milliseconds{ 300 };

                            auto task = [hot = optionalHot->hotkey, this]
                            {
                                LOG_DEBUG("MouseHotkeysModule simulating hot from async task: {}", Client::hotkeyToStdString(hot));
                                simulator.hotkey(hot);
                            };

                            asyncTaskManager.start(task, kDelay);
                        }
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
                {}
            }
        }
    }
}
