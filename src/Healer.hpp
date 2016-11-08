#pragma once

#include "ui/modules/healer/HealRule.hpp"
#include "Module.hpp"
#include "Simulator.hpp"
#include "tibiareader.hpp"

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

                Readers::details::TibiaReader reader;

                const Configs::HealerConfig &config;
                const Configs::AdvancedSettings &advancedSettings;

                void executeRule( const AMB::Modules::Heal::HealRule &rule );

                void runDetails();

            public:
                Healer(const Configs::HealerConfig &config,
                       const Configs::AdvancedSettings &advancedSettings,
                       Simulate::Simulator &simulator);
                ~Healer()
                {}

                void attachToNewWindow(HWND hwnd)
                {
                    reader.attachToNewWindow(hwnd);
                }
            };
        }
    }
}
