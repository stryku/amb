#pragma once

#include "ViewConfig.hpp"

namespace AMB
{
    namespace Modules
    {
        class ModuleView
        {
        public:
            virtual ~ModuleView()
            {}

            virtual ViewConfig toConfig() const = 0;
        };
    }
}