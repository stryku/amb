#include "config/ConfigFileManager.hpp"
#include "utils.hpp"

#include <string>
#include <fstream>

namespace Amb
{
    namespace Config
    {
        void ConfigFileManager::save(const std::string &configs, std::string path)
        {
            if (path.empty())
                path = currentFilePath;

            std::ofstream out(path);

            if (out.is_open())
            {
                currentFilePath = path;
                out << configs;
            }
        }

        std::string ConfigFileManager::load(const std::string &path)
        {
            currentFilePath = path;
            return Amb::Utils::readWholeFileIntoString(currentFilePath);
        }

        bool ConfigFileManager::isPathEmpty() const
        {
            return currentFilePath.empty();
        }
    }
}

