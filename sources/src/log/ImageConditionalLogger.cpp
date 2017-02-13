#include "log/ImageConditionalLogger.hpp"
#include "graphics/Image.hpp"

namespace Amb
{
    namespace Log
    {
        ImageConditionalLogger::ImageConditionalLogger(const std::string& loggerName, const std::string& path)
            : logger{ loggerName, path }
        {}

        void ImageConditionalLogger::log(const Graphics::Image& img)
        {
            const auto hash = img.hash();

            if (!shouldLog(hash))
                return;

            logger.log(img);
            alreadyLoggerImagesHashes.push_back(hash);
        }

        bool ImageConditionalLogger::shouldLog(const cexpr::hash_t hash) const
        {
            return externalBool && std::find(std::cbegin(alreadyLoggerImagesHashes),
                                             std::cend(alreadyLoggerImagesHashes),
                                             hash) == std::cend(alreadyLoggerImagesHashes);
        }

        void ImageConditionalLogger::setExternalBool(bool cond)
        {
            externalBool = cond;
        }
    }
}
