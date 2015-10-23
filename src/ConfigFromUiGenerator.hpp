#pragma once

#include <Configs.hpp>
#include <ModuleId.hpp>
#include <TibiaFinder.hpp>
#include <HealerRulesTable.hpp>

#include <mainwindow.h>

namespace AMB
{
    namespace Configs
    {
        class ConfigFromUiGenerator
        {
        public:
            ConfigFromUiGenerator( const Ui::MainWindow *&ui,
                                   const HealerRulesTable &healerRulesTable ) :
                ui( ui ),
                healerRulesTable( healerRulesTable )
            {}

            void regenerate()
            {
                regenerateCommon();
                regenerateAllModules();

            }

            void regenerateModule( Modules::ModuleId moduleId )
            {
                switch( moduleId )
                {
                    case ModuleId::HEALER: regenerateHealer();
                }
            }

        private:
            const Ui::MainWindow *&ui;
            const HealerRulesTable &healerRulesTable;
            AMB::Configs::GlobalConfig config;

            std::wstring getTibiaWindowTitle() const
            {
                const auto cbTibiaClients = ui->cbTibiaClients;
                auto variant = cbTibiaClients->currentData();

                return variant.toString().toStdWstring();
            }

            void regenerateHealer()
            {
                config.healerConfig.rules = healerRulesTable.getRules();
            }

            void regeneratePid()
            {
                auto title = getTibiaWindowTitle();

                config.pid = TibiaFinder::findProcessId( title );
            }

            void regenerateCommon()
            {
                regeneratePid();
            }

            void regenerateAllModules()
            {
                for( auto id = ModuleId::BEGIN;
                     id < ModuleId::END;
                     ++id )
                {
                    regenerateModule( id );
                }
            }
        };
    }
}
