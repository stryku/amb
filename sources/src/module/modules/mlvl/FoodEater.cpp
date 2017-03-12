#include "module/modules/mlvl/FoodEater.hpp"
#include "Simulator.hpp"
#include "log/log.hpp"
#include "utils/random/RandomBetween.hpp"

namespace Amb
{
    namespace Module
    {
        namespace Mlvl
        {
            FoodEater::FoodEater(Simulate::Simulator& simulator, Client::Hotkey hotkey)
                : simulator{ simulator }
                , hotkey{ hotkey }
                , nextEat{ std::chrono::system_clock::now() }
            {}

            void FoodEater::eat()
            {
                const auto current = std::chrono::system_clock::now();

                if (current > nextEat)
                {
                    const auto sec = Utils::Random::RandomBetween{ static_cast<size_t>(60),
                                                                   static_cast<size_t>(180) }.get();

                    nextEat = std::chrono::system_clock::now() + std::chrono::seconds(sec);

                    LOG_DEBUG("FoodEater pressing hotkey. Will sleep for: {}s", sec);
                    simulator.hotkey(hotkey);
                }
            }
        }
    }
}
