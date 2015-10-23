#pragma once

#include <Configs.hpp>
#include <ModuleId.hpp>
#include <TibiaFinder.hpp>

#include <mainwindow.h>

namespace AMB
{
    namespace Configs
    {
        class ConfigFromUiGenerator
        {
        public:
            ConfigFromUiGenerator( const Ui::MainWindow *&ui ) :
                ui( ui )
            {}

            void regenerate()
            {
                regenerateCommon();
                regenerateAllModules();

            }

            void regenerateModule( Modules::ModuleId moduleId )
            {

            }

        private:
            const Ui::MainWindow *&ui;
            AMB::Configs::GlobalConfig config;

            std::wstring getTibiaWindowTitle() const
            {
                const auto cbTibiaClients = ui->cbTibiaClients;
                auto variant = cbTibiaClients->currentData();

                return variant.toString().toStdWstring();
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
