#pragma once

#include <chrono>
#include <functional>

namespace Amb
{
    namespace Async
    {
        class AsyncTask
        {
        public:
            using Clock = std::chrono::system_clock;
            using Duration = std::chrono::milliseconds;
            using Task = std::function<void()>;

            AsyncTask(Task task, Duration delayDuration);

            bool tryExecute();

        private:
            std::chrono::time_point<Clock> startTime;
            Duration delayDuration;
            Task task;
        };
    }
}
