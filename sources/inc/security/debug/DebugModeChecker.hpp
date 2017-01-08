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
            private: 
                using Callback = std::function<void()>;

            public:
                DebugModeChecker(Callback debugModeDetectedCallback);
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

                Callback debugModeDetectedCallback;
                Utils::ThreadWorker threadWorker;
            };
        }
    }
}