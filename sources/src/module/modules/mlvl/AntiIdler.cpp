#include "module/modules/mlvl/AntiIdler.hpp"
#include "Simulator.hpp"
#include "log/log.hpp"

namespace Amb
{
    namespace Module
    {
        namespace Mlvl
        {
            AntiIdler::AntiIdler(Simulate::Simulator& simulator)
                : simulator{ simulator }
                , nextMove{ std::chrono::system_clock::now() }
                , waitRandom{ minWaitMs, maxWaitMs }
            {}

            void AntiIdler::andiIdle()
            {
                const auto current = std::chrono::system_clock::now();

                if (current > nextMove)
                {
                    const auto waitFor = waitRandom.get();

                    LOG_DEBUG("AntiIdler::antiIdle moving. Next wait time in: {}s", waitFor / 1000);

                    const auto movesCount = Utils::Random::RandomBetween{ 2, 6 }.get();

                    simulator.ctrlDown();

                    for (size_t i = 0; i < movesCount; ++i)
                        randMove();

                    simulator.ctrlUp();
                }
            }

            void AntiIdler::randMove()
            {
                const auto move = Utils::Random::RandomBetween{ 0, 3 }.get();
                constexpr WPARAM moves[] = { VK_LEFT, VK_UP, VK_DOWN, VK_RIGHT };

                simulator.keyDownAndUp(moves[move]);
            }
        }
    }
}