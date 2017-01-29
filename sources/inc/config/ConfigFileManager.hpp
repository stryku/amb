#pragma once

#include "utils/Observable.hpp"

#include <string>
#include <fstream>

namespace Amb
{
    namespace Config
    {
        class ConfigFileManager
        {
        public:
            ConfigFileManager() = default;
            ConfigFileManager(Utils::Observable<std::string>::CallbackType cb);

            void setPathObserver(Utils::Observable<std::string>::CallbackType cb)
            {
                currentFilePath.setCallback(cb);
            }

            bool save(const std::string &configs, std::string path = "");
            std::string load(const std::string &path);
            bool isPathEmpty() const;

        private:
            Utils::Observable<std::string> currentFilePath;
        };
    }
}
