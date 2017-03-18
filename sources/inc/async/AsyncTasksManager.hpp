#pragma once

#include <functional>
#include <chrono>

namespace Amb
{
    namespace Async
    {
        class AsyncTasksManager
        {
        public:
            using Task = std::function<void()>;

            void tick();
            void start(Task task, const std::chrono::milliseconds& ms);
            void stopAll();
        };
    }
}
