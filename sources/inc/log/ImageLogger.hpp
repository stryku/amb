#pragma once

#include <spdlog/spdlog.h>

#include <string>

namespace Amb
{
    namespace Graphics
    {
        struct Image;
    }

    namespace Log
    {
        class ImageLogger
        {
        public:
            ImageLogger(const std::string& loggerName, const std::string& path);

            void log(const Graphics::Image& img);

        private:
            std::shared_ptr<spdlog::logger> file{ nullptr };
        };
    }
}
