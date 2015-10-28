#pragma once

#include "Configs.hpp"
#include "TibiaStuffReader.hpp"
#include "Simulator.hpp"

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

            bool continueRun = true;

            virtual void runDetails() = 0;

            virtual void runMethod();

        public:
            Module( Memory::TibiaStuffReader &tibiaReader, 
                    Simulate::Simulator &simulator );
            ~Module();

            void run();

            void stop();

            bool isRunning() const;
        };
    }
}
