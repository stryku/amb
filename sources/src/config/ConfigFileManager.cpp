#include "config/ConfigFileManager.hpp"
#include "utils.hpp"

#include <string>
#include <fstream>

namespace Amb
{
    namespace Config
    {
        ConfigFileManager::ConfigFileManager(Utils::Observable<std::string>::CallbackType cb)
            : currentFilePath{ cb }
        {}

        bool ConfigFileManager::save(const std::string &configs, std::string path)
        {
            if (path.empty())
                path = currentFilePath.get();

            std::ofstream out(path);

            if (!out.is_open())
                return false;

            currentFilePath.set(path);
            out << configs;

            return true;
        }

        std::string ConfigFileManager::load(const std::string &path)
        {
            currentFilePath.set(path);
            return Amb::Utils::readWholeFileIntoString(currentFilePath.get());
        }

        bool ConfigFileManager::isPathEmpty() const
        {
            return currentFilePath.get().empty();
        }
    }
}

