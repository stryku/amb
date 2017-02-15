#pragma once

#include "utils/SimpleToStringConverter.hpp"

#include <spdlog/spdlog.h>

namespace Amb
{
    namespace Log
    {
        template <typename ToStringConverter = Amb::Utils::SimpleToStringConverter>
        class Logger
        {
        public:
            Logger(const std::string& loggerName, const std::string& path)
                : logger{ spdlog::basic_logger_mt(loggerName, path) }
            {}

            template <typename ...Args>
            void log(const Args&... args)
            {
                logger->info(ToStringConverter::convert(args...)); // todo std::forward
            }

        private:
            std::shared_ptr<spdlog::logger> logger;
        };
    }
}
