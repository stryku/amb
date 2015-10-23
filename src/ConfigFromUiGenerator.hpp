#pragma once

#include <Configs.hpp>
#include <ModuleId.hpp>

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

            }

            void regenerateModule( Modules::ModuleId moduleId )
            {

            }

        private:
            const Ui::MainWindow *&ui;
            AMB::Configs::GlobalConfig config;
        };
    }
}
