#pragma once

#include "module/ModuleId.hpp"

#include <unordered_map>
#include <memory>

namespace Ui
{
    class MainWindow;
}

namespace Amb
{
    namespace Monitor
    {
        namespace Mouse
        {
            class MouseMonitorFactory;
        }
    }

    namespace Config
    {
        struct GlobalConfig;
    }

    namespace Simulate
    {
        class Simulator;
    }

    namespace Module
    {
        class ModuleCore;

        class Factory
        {
        public:
            Factory(::Ui::MainWindow *ui)
                : ui{ ui }
            {}

            std::unordered_map<ModuleId, std::unique_ptr<ModuleCore>> create(const Config::GlobalConfig &config,
                                                                             Simulate::Simulator &simulator,
                                                                             Monitor::Mouse::MouseMonitorFactory& mousMonitorFactory);

        private:
            ::Ui::MainWindow *ui;
        };
    }
}

