#pragma once

#include "log/ImageLogger.hpp"

#include <cexpr/crypto.hpp>

#include <vector>

namespace Amb
{
    namespace Log
    {
        template <typename Condition>
        class ImageConditionalLogger
        {
        public:
            ImageConditionalLogger(const std::string& loggerName, const std::string& path)
                : logger{ loggerName, path }
            {}

            void log(const Graphics::Image& img)
            {
                const auto hash = img.hash();

                if (!condition.shouldLog(hash))
                    return;

                condition.willLogThis(hash);
                logger.log(img);
                alreadyLoggerImagesHashes.push_back(hash);
            }
            void setExternalBool(bool cond)
            {
                condition.setExternalBool(cond);
            }

        private:
            ImageLogger logger;
            std::vector<cexpr::hash_t> alreadyLoggerImagesHashes;
            Condition condition;
        };
    }
}
