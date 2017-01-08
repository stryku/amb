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

                template <typename Format, typename ...Args>
                void log(const Format &format, const Args&... args)
                {
                    console->info(format, args...);
                    file->info(format, args...);
                    console->flush();
                    file->flush();
                }

                static Logger& get();

            private:
                std::shared_ptr<spdlog::logger> console{ nullptr };
                std::shared_ptr<spdlog::logger> file{ nullptr };
            };
        }
    }
}
