#include "module/ModulesFactory.hpp"
#include "module/ModuleCore.hpp"

#include "Configs.hpp"
#include "Simulator.hpp"
#include "utils/Structs.hpp"
#include "db/Items.hpp"

#include "ui_mainwindow.h"

#include "module/modules/Healer.hpp"
#include "module/modules/LooterModule.hpp"
#include "module/modules/mlvl/MlvlModule.hpp"
#include "client/reader/TibiaClientMemoryReader.hpp"
#include "client/window/finder/DeadCreatureWindowFinderFactory.hpp"

namespace 
{
    std::unique_ptr<Amb::Module::Heal::Healer> createHealer(const Amb::Configs::GlobalConfig &config,
                                                            Amb::Simulate::Simulator &simulator)
    {
        return std::make_unique<Amb::Module::Heal::Healer>(config.healerConfig,
                                                           config.advancedSettings,
                                                           simulator,
                                                           config.tibiaClientWindowInfo);
    }

    std::unique_ptr<Amb::Module::Looter::LooterModule> createLooter(const Amb::Configs::GlobalConfig &config,
                                                                    Amb::Simulate::Simulator &simulator)
    {
        using TibiaReader = Amb::Client::Reader::TibiaClientMemoryReader;

        return std::make_unique<Amb::Module::Looter::LooterModule>(config.looter,
                                                                   config.advancedSettings,
                                                                   simulator,
                                                                   config.tibiaClientWindowInfo,
                                                                   Amb::Client::Window::Finder::DeadCreatureWindowFinderFactory{},
                                                                   std::make_unique<TibiaReader>(config.pid));
    }
    
    std::unique_ptr<Amb::Module::Mlvl::MlvlModule> createMlvl(const Amb::Configs::GlobalConfig &config,
                                                              Amb::Simulate::Simulator &simulator)
    {
        return std::make_unique<Amb::Module::Mlvl::MlvlModule>(config.mlvl,
                                                               config.advancedSettings,
                                                               simulator,
                                                               config.tibiaClientWindowInfo);
    }
}

namespace Amb
{
    namespace Module
    {
        std::unordered_map<ModuleId, std::unique_ptr<ModuleCore>> Factory::create(const Configs::GlobalConfig &config,
                                                                                  Simulate::Simulator &simulator)
        {
            std::unordered_map<ModuleId, std::unique_ptr<ModuleCore>> map;

            map[ModuleId::MOD_HEALER] = createHealer(config, simulator);
            map[ModuleId::MOD_LOOTER] = createLooter(config, simulator);
            map[ModuleId::MOD_MLVL] = createMlvl(config, simulator);

            return std::move(map);
        }
    }
}
