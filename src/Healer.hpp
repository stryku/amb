#pragma once

#include "HealRule.hpp"
#include "Module.hpp"

#include <chrono>

namespace AMB
{
    namespace Modules
    {
        namespace Heal
        {
            class Healer : public Module
            {
            private:
                size_t sleepMin = 700, 
                       sleepMax = 800;

                void runDetails()
                {
                }

            public:
                Healer( Configs::GlobalConfig &config ) :
                    Module( config )
                {}
                ~Healer()
                {}


            };
        }
    }
}