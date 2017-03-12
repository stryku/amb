#pragma once

#include "module/ModuleCore.hpp"
#include "log/details/Logger.hpp"
#include "mouse/MouseEvent.hpp"

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
                class MouseHotkeysModule final : public ModuleCore
                {
                public:
                    MouseHotkeysModule(Simulate::Simulator &simulator,
                                       const Client::TibiaClientWindowInfo &tibiaClientWindowInfo,
                                       const Config::Module::MouseHotkeysConfig& mouseHotkeysConfig,
                                       Monitor::Mouse::MouseMonitorFactory& mouseMonitorFactory);
                    ~MouseHotkeysModule();

                    void run() override;
                    void stop() override;

                private:
                    void runDetails() override;
                    void applyConfigs() override;
                    void mouseEventCallback(Mouse::MouseEvent ev);

                    const Config::Module::MouseHotkeysConfig& mouseHotkeysConfig;
                    std::unique_ptr<Monitor::Mouse::IMouseMonitor> mouseMonitor;
                };
            }
        }
    }
}
