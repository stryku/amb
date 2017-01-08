#include "security/debug/DebugModeCheckerFactory.hpp"

namespace Amb
{
    namespace Security
    {
        namespace Debug
        {
            DebugModeCheckerFactory::RetType DebugModeCheckerFactory::create(DebugModeChecker::CallbackType
#ifdef AMB_PREVENT_DEBUG
                                                                             cb
#endif
            ) const
            {
#ifdef AMB_PREVENT_DEBUG
                return std::make_unique<DebugModeChecker>(cb);
#else
                return 0;
#endif
            }
        }
    }
}
