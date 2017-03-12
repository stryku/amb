#pragma once

#include "client/Hotkey.hpp"

#include <chrono>

namespace Amb
{
    namespace Simulate
    {
        class Simulator;
    }

    namespace Module
    {
        namespace Mlvl
        {
            class FoodEater
            {
            public:
                explicit FoodEater(Simulate::Simulator& simulator, Client::Hotkey hotkey);

                void eat();

            private:
                Simulate::Simulator& simulator;
                Client::Hotkey hotkey;
                std::chrono::time_point<std::chrono::system_clock> nextEat;
            };
        }
    }
}
