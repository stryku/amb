#pragma once

#include "log/ImageLogger.hpp"

#include <cexpr/crypto.hpp>

#include <vector>

namespace Amb
{
    namespace Log
    {
        class ImageConditionalLogger
        {
        public:
            ImageConditionalLogger(const std::string& loggerName, const std::string& path);

            void log(const Graphics::Image& img);
            void setExternalBool(bool cond);

        private:
            bool shouldLog(const cexpr::hash_t hash) const;

            ImageLogger logger;
            bool externalBool{ true };
            std::vector<cexpr::hash_t> alreadyLoggerImagesHashes;
        };
    }
}
