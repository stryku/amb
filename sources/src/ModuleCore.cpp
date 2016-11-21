#include "ModuleCore.hpp"

namespace AMB
{
    namespace Modules
    {
        void ModuleCore::runMethod()
        {
            try
            {
                applyConfigs();
                while (continueRun)
                    runDetails();
            }
            catch (std::exception& e)
            {
                qDebug("ModuleCore cought exception: %s", e.what());
            }
        }

        ModuleCore::ModuleCore(Simulate::Simulator &simulator) :
            simulator( simulator )
        {}
        ModuleCore::~ModuleCore()
        {
            stop();
        }

        void ModuleCore::run()
        {
            auto runLambda = [this] {runMethod(); };

            continueRun = true;

            runThread = std::make_unique<std::thread>( runLambda );
        }

        void ModuleCore::stop()
        {
            continueRun = false;

            if (runThread != nullptr && runThread->joinable())
                runThread->join();
        }

        bool ModuleCore::isRunning() const
        {
            return continueRun;
        }
    }
}
