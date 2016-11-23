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
    namespace Configs
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

            std::unordered_map<ModuleId, std::unique_ptr<ModuleCore>> create(const Configs::GlobalConfig &config,
                                                                             Simulate::Simulator &simulator);

        private:
            ::Ui::MainWindow *ui;
        };
    }
}

