#pragma once

#include "Configs.hpp"
#include "Simulator.hpp"
#include "capture/FrameCapturer.hpp"
#include "utils/Structs.hpp"
#include "client/TibiaClientType.hpp"
#include "client/TibiaClientWindowInfo.hpp"

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

            //virtual void setTibiaClientType(Client::TibiaClientType type) = 0;
            void attachToNewWindow(HWND hwnd);

        protected:
            std::unique_ptr<std::thread> runThread;
            Simulate::Simulator &simulator;
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
