﻿#pragma once

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

            virtual void run();
            virtual void stop();
            bool isRunning() const;

            virtual void attachToNewWindow(HWND hwnd);
            virtual void setEnableDebugLogs(bool enabled) {};

            virtual void attachToNewProcess(DWORD pid) {}

        protected:
            HWND hwnd;
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
