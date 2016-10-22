#include "Module.hpp"

namespace AMB
{
    namespace Modules
    {
        void Module::runMethod()
        {
            while( continueRun )
                runDetails();
        }

        Module::Module( Memory::TibiaStuffReader &tibiaReader,
                        Simulate::Simulator &simulator ) :
            tibiaReader( tibiaReader ),
            simulator( simulator )
        {}
        Module::~Module()
        {
            stop();
        }

        void Module::run()
        {
            auto runLambda = std::bind( &Module::runMethod, this );

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
