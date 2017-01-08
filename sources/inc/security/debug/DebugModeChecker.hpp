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

                Callback debugModeDetectedCallback;
                Utils::ThreadWorker threadWorker;
            };
        }
    }
}