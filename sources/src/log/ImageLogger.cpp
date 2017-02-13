#include "log/ImageLogger.hpp"
#include "graphics/Image.hpp"
#include "utils.hpp"

namespace Amb
{

    namespace Log
    {
        ImageLogger::ImageLogger(const std::string& loggerName, const std::string& path)
            : file{ spdlog::basic_logger_mt(loggerName, path) }
        {}

        void ImageLogger::log(const Graphics::Image& img)
        {
            file->info(Utils::imageToSimpleString(img));
        }
    }
}
