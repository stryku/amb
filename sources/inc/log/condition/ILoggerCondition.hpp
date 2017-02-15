#pragma once

namespace Amb
{
    namespace Log
    {
        namespace Condition
        {
            template <typename ...Args>
            class ILoggerCondition
            {
            public:
                virtual bool shouldLog(const Args&... args) = 0;
                virtual bool willLogThis(const Args&... args) = 0;

            };
        }
    }
}
