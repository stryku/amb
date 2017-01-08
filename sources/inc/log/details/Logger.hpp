#pragma once

#include <spdlog/spdlog.h>

namespace Amb
{
    namespace Log
    {
        namespace details
        {
            class Logger
            {
            public:
                static constexpr const char* LoggerName = "logger";

                explicit Logger();
                ~Logger();

            private:
                std::shared_ptr<spdlog::logger> logger{ nullptr };
            };
        }
    }
}
