#pragma once

namespace Amb
{
    namespace Log
    {
        class ILogger
        {
        public:
            template <typename ...Args>
            virtual void log(const Args&... args) = 0;
        };
    }
}
