#include "Module.hpp"

namespace AMB
{
    namespace Modules
    {
        void Module::runMethod()
        {
            try
            {
                while (continueRun)
                    runDetails();
            }
            catch (std::exception& e)
            {
                qDebug("Module cought exception: %s", e.what());
            }
        }

        Module::Module(Simulate::Simulator &simulator) :
            simulator( simulator )
        {}
        Module::~Module()
        {
            stop();
        }

        void Module::run()
        {
            auto runLambda = [this] {runMethod(); };

            continueRun = true;

            runThread = std::make_unique<std::thread>( runLambda );
        }

        void Module::stop()
        {
            continueRun = false;

            if( runThread->joinable() )
                runThread->join();
        }

        bool Module::isRunning() const
        {
            return continueRun;
        }
    }
}
