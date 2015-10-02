#pragma once

#include "Configs.hpp"

#include <thread>
#include <memory>

namespace AMB
{
    namespace Modules
    {
        class Module
        {
        protected:
            Configs::GlobalConfig &config;
            std::unique_ptr<std::thread> runThread;
            bool continueRun = true;

            virtual void runDetails() = 0;

            void runMethod()
            {
                while( continueRun )
                    runDetails();
            }

        public:
            Module( Configs::GlobalConfig &config ) :
                config( config )
            {}
            ~Module()
            {
                stop();
            }

            void run()
            {
                auto run = std::bind( &Module::runMethod, this );

                runThread = std::make_unique<std::thread>( run );
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