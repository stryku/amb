#include "module/modules/mlvl/MlvlSpellCaster.hpp"
#include "client/reader/HealthManaReader.hpp"
#include "Simulator.hpp"
#include "log/log.hpp"

#include <chrono>

namespace Amb
{
    namespace Module
    {
        namespace Mlvl
        {
            SpellCaster::SpellCaster(Simulate::Simulator& simulator,
                                     Client::Reader::HealthManaReader& healthManaReader,
                                     Client::Hotkey hotkey,
                                     size_t percentFrom,
                                     size_t percentTo)
                : simulator{ simulator }
                , healthManaReader{ healthManaReader }
                , hotkey{ hotkey }
                , percentRand{ percentFrom, percentTo }
                , nextPercentToCast{ 0 }
            {
            }

            void SpellCaster::cast(const RelativeRect& lastCapturedRect)
            {
                const auto currentPercent = healthManaReader.getManaPercent(lastCapturedRect);

                if (currentPercent >= nextPercentToCast)
                {
                    nextPercentToCast = percentRand.get();
                    LOG_DEBUG("SpellCaster casting. Next percent: {}", nextPercentToCast);
                    simulator.hotkey(hotkey);
                }
            }
        }
    }
}
