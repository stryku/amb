#include "client/TibiaClientWindowRectObserver.hpp"
#include "utils/Structs.hpp"

#include <thread>

#include <Windows.h>

namespace Amb
{
    namespace Client
    {
        TibiaClientWindowRectObserver::TibiaClientWindowRectObserver(Observable::CallbackType cb)
            : rect{ cb }
        {}

        auto TibiaClientWindowRectObserver::getLoopFunction(HWND tibiaWindowHandle)
        {
            return [this, tibiaWindowHandle]
            {
                RECT rc;
                GetClientRect(tibiaWindowHandle, &rc);
                if (rc.bottom == 0 && rc.right == 0)
                {
                    qDebug("Window is minimized!");
                    return;
                }

                rect.set(Rect::fromWindowsRect(rc));
            };
        }

        void TibiaClientWindowRectObserver::run(HWND tibiaWindowHandle)
        {
            thread.start(getLoopFunction(), 
                         Utils::RandomBetween{ 500,500 });
        }

        void TibiaClientWindowRectObserver::attachToNewWindow(HWND tibiaWindowHandle)
        {
            thread.stop();
            run(tibiaWindowHandle);
        }

    }
}
