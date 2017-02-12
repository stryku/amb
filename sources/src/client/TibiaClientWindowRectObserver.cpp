#include "client/TibiaClientWindowRectObserver.hpp"
#include "log/log.hpp"

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
                ClientToScreen(tibiaWindowHandle, reinterpret_cast<POINT*>(&rcOnMonitor.left));
                ClientToScreen(tibiaWindowHandle, reinterpret_cast<POINT*>(&rcOnMonitor.right));
                if (rc.bottom == 0 && rc.right == 0)
                {
                    LOG_DEBUG("Window is minimized!");
                    return;
                }

                LOG_DEBUG("TibiaClientWindowRectObserver Rect: { %d, %d, %d, %d }!", rcOnMonitor.left, rcOnMonitor.right, rcOnMonitor.top, rcOnMonitor.bottom);

                TibiaClientWindowInfo value;
                value.rect = Rect::fromWindowsRect(rc);
                value.rectOnMonitors = Rect::fromWindowsRect(rcOnMonitor);
                value.corners = RectCorners::fromRect(value.rect);

                rect.set(value);
            };
        }

        void TibiaClientWindowRectObserver::run(HWND tibiaWindowHandle)
        {
            LOG_DEBUG("TibiaClientWindowRectObserver::run");

            if (tibiaWindowHandle == NULL)
            {
                LOG_DEBUG("TibiaClientWindowRectObserver::run window handle is NULL");
                return;
            }

            LOG_DEBUG("TibiaClientWindowRectObserver Starting!");
            thread.start(getLoopFunction(tibiaWindowHandle),
                         Utils::RandomBetween{ 1000,1000 });
        }

        void TibiaClientWindowRectObserver::attachToNewWindow(HWND tibiaWindowHandle)
        {
            thread.stop();
            run(tibiaWindowHandle);
        }

    }
}
