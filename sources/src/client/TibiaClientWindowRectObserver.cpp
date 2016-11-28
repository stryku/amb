#include "client/TibiaClientWindowRectObserver.hpp"

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
                RECT rcOnMonitor = rc;
                ClientToScreen(tibiaWindowHandle, reinterpret_cast<POINT*>(&rc.left));
                ClientToScreen(tibiaWindowHandle, reinterpret_cast<POINT*>(&rc.right));
                if (rc.bottom == 0 && rc.right == 0)
                {
                    qDebug("Window is minimized!");
                    return;
                }

                qDebug("TibiaClientWindowRectObserver Rect: { %d, %d, %d, %d }!", rcOnMonitor.left, rcOnMonitor.right, rcOnMonitor.top, rcOnMonitor.bottom);

                TibiaClientWindowInfo value;
                value.rect = Rect::fromWindowsRect(rc);
                value.rectOnMonitors = Rect::fromWindowsRect(rcOnMonitor);

                rect.set(value);
            };
        }

        void TibiaClientWindowRectObserver::run(HWND tibiaWindowHandle)
        {
            qDebug("TibiaClientWindowRectObserver::run( %x )", tibiaWindowHandle);
            if (tibiaWindowHandle != NULL)
            {
                qDebug("TibiaClientWindowRectObserver Starting!");
                thread.start(getLoopFunction(tibiaWindowHandle),
                             Utils::RandomBetween{ 1000,1000 });
            }
        }

        void TibiaClientWindowRectObserver::attachToNewWindow(HWND tibiaWindowHandle)
        {
            thread.stop();
            run(tibiaWindowHandle);
        }

    }
}
