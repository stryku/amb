#pragma once

#include "Configs.hpp"
#include "ModuleView.hpp"
#include "TibiaStuffReader.hpp"

#include <thread>
#include <memory>

namespace AMB
{
    namespace Modules
    {
        class Module
        {
        protected:
            std::unique_ptr<std::thread> runThread;
            Memory::TibiaStuffReader &tibiaReader;
            Simulate::Simulator &simulator;
            const void *ui; //todo

            bool continueRun = true;

            virtual void runDetails() = 0;
            virtual void initConfig() = 0;

            virtual void runMethod()
            {
                initConfig();

                while( continueRun )
                    runDetails();
            }

        public:
            Module( Memory::TibiaStuffReader &tibiaReader, 
                    Simulate::Simulator &simulator ) : // todo add to ptr to ui to module get controls from view
                tibiaReader( tibiaReader ),
                simulator( simulator )
            {}
            ~Module()
            {
                stop();
            }

            void run()
            {
                auto runLambda = std::bind( &Module::runMethod, this );

                runThread = std::make_unique<std::thread>( runLambda );
            }

            void stop()
            {
                continueRun = false;

                if( runThread->joinable() )
                    runThread->join();
            }
        };
    }
}