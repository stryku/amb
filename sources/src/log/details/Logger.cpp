#include "log/details/Logger.hpp"

#include <spdlog/spdlog.h>

namespace Amb
{
    namespace Log
    {
        namespace details
        {
            Logger::Logger()
            {
                std::vector<spdlog::sink_ptr> sinks;
                sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
                sinks.push_back(std::make_shared<spdlog::sinks::simple_file_sink_mt>("log.txt"));
                logger = std::make_shared<spdlog::logger>(LoggerName, std::begin(sinks), std::end(sinks));
            }

            Logger::~Logger()
            {
                spdlog::drop_all();
            }
        }
    }
}

