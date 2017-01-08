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
                file = spdlog::basic_logger_mt("file_logger", "lodadsdg.txt");
                console = spdlog::stdout_color_mt("console");
            }


            Logger& Logger::get()
            {
                static Logger l;
                return l;
            }

            Logger::~Logger()
            {
                spdlog::drop_all();
            }
        }
    }
}

