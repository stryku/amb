#include "async/AsyncTask.hpp"

#include <boost/assert.hpp>

namespace Amb
{
    namespace Async
    {
        AsyncTask::AsyncTask(Task task, Duration delayDuration)
            : startTime{ Clock::now() }
            , delayDuration{ delayDuration }
            , task{ task }
        {}

        bool AsyncTask::tryExecute()
        {
            if (Clock::now() < startTime + delayDuration)
                return false;

            BOOST_ASSERT_MSG(task, "AsyncTask::task should be always valid");

            task();
            return true;
        }
    }
}
