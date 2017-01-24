#pragma once

#include "Configs.hpp"
#include "Simulator.hpp"
#include "capture/FrameCapturer.hpp"
#include "utils/Structs.hpp"
#include "client/TibiaClientType.hpp"
#include "client/TibiaClientWindowInfo.hpp"
#include "simulate/MouseSimulator.hpp"
#include "client/reader/TibiaClientReader.hpp"

#include <thread>
#include <memory>

namespace Amb
{
    namespace Module
    {
        class ModuleCore
        {
        public:
            explicit ModuleCore(Simulate::Simulator &simulator,
                                const Client::TibiaClientWindowInfo &tibiaClientWindowInfo,
                                std::unique_ptr<Client::Reader::TibiaClientReader> tibiaClientReader = nullptr);
            virtual ~ModuleCore();

            void run();
            void stop();
            bool isRunning() const;

            void attachToNewWindow(HWND hwnd);

            virtual void attachToNewProcess(DWORD pid) {}

        protected:
            std::unique_ptr<std::thread> runThread;
            Simulate::Simulator &simulator;
            Simulate::MouseSimulator mouseSimulator;
            Graphics::Image screen;
            Capture::FrameCapturer frameCapturer;
            const Client::TibiaClientWindowInfo &tibiaClientWindowInfo;
            std::unique_ptr<Client::Reader::TibiaClientReader> tibiaClientReader;

            bool continueRun{ false };

            void newFrame();

            virtual void runDetails() = 0;
            virtual void runMethod();
            virtual void applyConfigs() = 0;
        };
    }
}
