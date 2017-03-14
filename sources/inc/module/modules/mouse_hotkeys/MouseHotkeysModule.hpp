#pragma once

#include "module/ModuleCore.hpp"
#include "log/details/Logger.hpp"
#include "mouse/MouseEvent.hpp"

#include <boost/optional.hpp>

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            class IMouseMonitor;
            class MouseMonitorFactory;
        }
    }

    namespace Config
    {
        struct GlobalConfig;

        namespace Module
        {
            struct MouseHotkeysConfig;
        }
    }

    namespace Module
    {
        namespace Modules
        {
            namespace MouseHotkeys
            {
                struct MouseHotkey;

                class MouseHotkeysModule final : public ModuleCore
                {
                public:
                    MouseHotkeysModule(Simulate::Simulator &simulator,
                                       const Client::TibiaClientWindowInfo &tibiaClientWindowInfo,
                                       const Config::GlobalConfig& globalConfig,
                                       const Config::Module::MouseHotkeysConfig& mouseHotkeysConfig,
                                       Monitor::Mouse::MouseMonitorFactory& mouseMonitorFactory);
                    ~MouseHotkeysModule();

                    void run() override;
                    void stop() override;

                    void attachToNewProcess(DWORD pid) override;

                private:
                    void runDetails() override;
                    void applyConfigs() override;
                    void mouseEventCallback(Mouse::MouseEvent ev);

                    bool tibiaIsOnTop();

                    boost::optional<MouseHotkey> getHotkeyForEvent(const Mouse::MouseEvent& ev) const;

                    const Config::Module::MouseHotkeysConfig& mouseHotkeysConfig;
                    const Config::GlobalConfig& globalConfig;
                    std::unique_ptr<Monitor::Mouse::IMouseMonitor> mouseMonitor;
                    DWORD currentTibiaPid{ NULL };
                };
            }
        }
    }
}
