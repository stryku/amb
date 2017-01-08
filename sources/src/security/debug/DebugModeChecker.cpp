#include "security/debug/DebugModeChecker.hpp"

namespace Amb
{
    namespace Security
    {
        namespace Debug
        {
            DebugModeChecker::DebugModeChecker(Callback debugModeDetectedCallback)
            {
                threadWorker.start(debugModeDetectedCallback, delayDuration);

            }

            DebugModeChecker::~DebugModeChecker()
            {
                threadWorker.stop();
            }
        }
    }
}