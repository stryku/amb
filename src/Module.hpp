#pragma once

#include "Configs.hpp"
#include "Simulator.hpp"

#include <thread>
#include <memory>

namespace AMB
{
    namespace Modules
    {
        class Module
        {
        protected:
            std::unique_ptr<std::thread> runThread;
            Simulate::Simulator &simulator;

            bool continueRun = false;

            virtual void runDetails() = 0;
            virtual void runMethod();

        public:
            Module(Simulate::Simulator &simulator);
            ~Module();

            void run();
            void stop();
            bool isRunning() const;
            virtual void attachToNewWindow(HWND hwnd) = 0;
        };
    }
}
