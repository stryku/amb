#pragma once

#include "utils/Observable.hpp"
#include "utils/ThreadWorker.hpp"
#include "client/TibiaClientWindowInfo.hpp"
#include "log/ConditionalLogger.hpp"
#include "log/condition/LogDifferentThanLastCondition.hpp"
#include "log/RectLogger.hpp"

#include <Windows.h>

namespace Amb
{
    namespace Client
    {
        class TibiaClientWindowRectObserver
        {
        private:
            using Observable = Utils::Observable<TibiaClientWindowInfo>;

        public:
            TibiaClientWindowRectObserver(Observable::CallbackType cb);

            void run(HWND tibiaWindowHandle = NULL);
            void attachToNewWindow(HWND tibiaWindowHandle);

        private:
            using Logger = Log::ConditionalLogger<Log::Condition::LogDifferentThanLastCondition<Rect>,
                                                  Log::RectLogger,
                                                  Rect>;
            auto getLoopFunction(HWND tibiaWindowHandle);

            Utils::ThreadWorker thread;
            Observable rect;
            Logger logger;
        };
    }
}
