#pragma once

#include "security/debug/DebugModeChecker.hpp"
#include <memory>


namespace Amb
{
    namespace Security
    {
        namespace Debug
        {
            class DebugModeCheckerFactory
            {
            private:
#ifdef AMB_PREVENT_DEBUG
                using RetType = std::unique_ptr<DebugModeChecker>;
#else
                using RetType = int;
#endif

            public:
                RetType create(DebugModeChecker::CallbackType 
#ifdef AMB_PREVENT_DEBUG
                               cb
#endif
                ) const;
            };
        }
    }

}
