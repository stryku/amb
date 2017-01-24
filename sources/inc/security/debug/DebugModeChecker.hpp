#pragma once

#include "utils/ThreadWorker.hpp"

#include <functional>

namespace Amb
{
    namespace Security
    {
        namespace Debug
        {
            class DebugModeChecker
            {
            public:
                using CallbackType = std::function<void()>;

                DebugModeChecker(CallbackType debugModeDetectedCallback);
                ~DebugModeChecker();

            private:
                constexpr static size_t loopDelayMs = 500;
                constexpr static auto delayDuration = std::chrono::milliseconds{ loopDelayMs };

                bool isDebugged() const;

                bool checkIsDebuggerPresent() const;
                bool checkIsDebugged() const;
                bool checkNtGlobalFlags() const;
                bool checkHeapFlags() const;
                bool checkVista() const;
                bool checkNtQueryInformationProcess() const;
                bool checkCheckRemoteDebuggerPresent() const;

                CallbackType debugModeDetectedCallback;
                Utils::ThreadWorker threadWorker;
            };
        }
    }
}