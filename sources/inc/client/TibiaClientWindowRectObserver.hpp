#pragma once

#include "utils/Observable.hpp"
#include "utils/ThreadWorker.hpp"
#include "client/TibiaClientWindowInfo.hpp"

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
            auto getLoopFunction(HWND tibiaWindowHandle);

            Utils::ThreadWorker thread;
            Observable rect;
        };
    }
}
