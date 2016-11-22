#pragma once

#include <string>
#include <fstream>

namespace Amb
{
    namespace Config
    {
        class ConfigFileManager
        {
        public:
            void save(const std::string &configs, std::string path = "");
            std::string load(const std::string &path);
            bool isPathEmpty() const;

        private:
            std::string currentFilePath;
        };
    }
}
