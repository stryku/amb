#include "utils/ThreadWorker.hpp"

namespace Amb
{
    namespace Utils
    {
        ThreadWorker::~ThreadWorker()
        {
            stop();
        }

        void ThreadWorker::stop()
        {
            if (needRunning)
            {
                needRunning = false;

                if (thread.joinable())
                    thread.join();
            }
        }

    }
}
