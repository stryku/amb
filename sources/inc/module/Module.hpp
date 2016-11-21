#pragma once

#include <memory>

namespace Amb
{
    namespace Module
    {
        class ModuleCore;
        class ModuleUiRemover;

        class Module
        {
        public:
            virtual ~Module() {}

            void run();
            void hideUi();

        private:
            //std::unique_ptr<ModuleCore> moduleCore;
            //std::unique_ptr<ModuleUiRemover> moduleUiRemover;
        };
    }
}
