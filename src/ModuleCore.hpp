#pragma once

#include "Configs.hpp"
#include "Simulator.hpp"

#include <thread>
#include <memory>

namespace AMB
{
    namespace Modules
    {
        class ModuleCore
        {
        protected:
            std::unique_ptr<std::thread> runThread;
            Simulate::Simulator &simulator;

            bool continueRun = false;

            virtual void runDetails() = 0;
            virtual void runMethod();
            virtual void applyConfigs() = 0;

        public:
            ModuleCore(Simulate::Simulator &simulator);
            ~ModuleCore();

            void run();
            void stop();
            bool isRunning() const;
            virtual void attachToNewWindow(HWND hwnd) = 0;
        };
    }
}
