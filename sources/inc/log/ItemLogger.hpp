#pragma once

#include "cexpr/crypto.hpp"

#include <spdlog/spdlog.h>

#include <vector>
#include <string>

namespace Amb
{
    namespace Graphics
    {
        struct Image;
    }

    namespace Log
    {
        class ItemLogger
        {
        public:
            ItemLogger(const std::string& path = "logs/missing_items_log.txt");
            void logItem(const Graphics::Image& img);

        private:
            bool isAlreadyLogged(const cexpr::hash_t imgHash) const;
            std::vector<cexpr::hash_t> alreadyLoggerItems;
            std::shared_ptr<spdlog::logger> file_logger{ nullptr };
        };
    }
}
