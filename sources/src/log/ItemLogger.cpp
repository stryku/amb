#include "log/ItemLogger.hpp"
#include "graphics/Image.hpp"
#include "utils.hpp"

#include <algorithm>

namespace Amb
{
    namespace Log
    {
        ItemLogger::ItemLogger(const std::string& path)
            : file_logger(spdlog::basic_logger_mt("items log", path))
        {}

        void ItemLogger::logItem(const Graphics::Image& img)
        {
            const auto imgHash = img.hash();

            if (isAlreadyLogged(imgHash))
                return;

            alreadyLoggerItems.push_back(imgHash);
            file_logger->info("%s", Utils::imageToSimpleString(img));
        }

        bool ItemLogger::isAlreadyLogged(const cexpr::hash_t imgHash) const
        {
            return std::find(std::cbegin(alreadyLoggerItems),
                             std::cend(alreadyLoggerItems),
                             imgHash) != std::cend(alreadyLoggerItems);
        }
    }
}
