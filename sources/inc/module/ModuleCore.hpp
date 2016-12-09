#pragma once

#include "Configs.hpp"
#include "Simulator.hpp"
#include "capture/FrameCapturer.hpp"
#include "utils/Structs.hpp"
#include "client/TibiaClientType.hpp"
#include "client/TibiaClientWindowInfo.hpp"
#include "simulate/MouseSimulator.hpp"

#include <thread>
#include <memory>

namespace Amb
{

    namespace Module
    {
        class ModuleCore
        {
        public:
            explicit ModuleCore(Simulate::Simulator &simulator, const Client::TibiaClientWindowInfo &tibiaClientWindowInfo);
            ~ModuleCore();

            void run();
            void stop();
            bool isRunning() const;

            void attachToNewWindow(HWND hwnd);

        protected:
            std::unique_ptr<std::thread> runThread;
            Simulate::Simulator &simulator;
            Simulate::MouseSimulator mouseSimulator;
            Graphics::Image screen;
            Capture::FrameCapturer frameCapturer;
            const Client::TibiaClientWindowInfo &tibiaClientWindowInfo;

            bool continueRun{ false };

            void newFrame();

            virtual void runDetails() = 0;
            virtual void runMethod();
            virtual void applyConfigs() = 0;
        };
    }
}
