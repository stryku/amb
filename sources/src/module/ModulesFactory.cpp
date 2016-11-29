#include "module/ModulesFactory.hpp"
#include "module/ModuleCore.hpp"

#include "Configs.hpp"
#include "Simulator.hpp"
#include "utils/Structs.hpp"

#include "ui_mainwindow.h"

#include "module/modules/Healer.hpp"
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
}


#ifdef AMB_PRO_COMPILATION
namespace
{

}
#else
#include "module/ui_remover/LooterUiRemover.hpp"
namespace
{
    void removeProVersionUi(::Ui::MainWindow *ui)
    {
        const Amb::Module::UiRemover::LooterUiRemover looter;
        looter.remove(ui);
    }
}
#endif //MODULE_COMPILE_LOOTER



namespace Amb
{
    namespace Module
    {
        std::unordered_map<ModuleId, std::unique_ptr<ModuleCore>> Factory::create(const Configs::GlobalConfig &config,
                                                                                  Simulate::Simulator &simulator)
        {
            std::unordered_map<ModuleId, std::unique_ptr<ModuleCore>> map;

#ifdef AMB_PRO_COMPILATION
            map[ModuleId::MOD_HEALER] = createHealer(config, simulator);
#else
            removeProVersionUi(ui);
#endif //MODULE_COMPILE_LOOTER

            return std::move(map);
        }
    }
}
