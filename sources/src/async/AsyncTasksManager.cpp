#include "async/AsyncTasksManager.hpp"
#include "log/log.hpp"

namespace Amb
{
    namespace Async
    {
        void AsyncTasksManager::tick()
        {
            std::vector<Utils::TokensProvider::Token> finishedTasks;

            for (auto& taskPair : tasks)
            {
                const auto token = taskPair.first;
                auto& task = taskPair.second;

                if (task.tryExecute())
                    finishedTasks.push_back(token);
            }

            if (!finishedTasks.empty())
                removeTasksFromList(finishedTasks);
        }

        void AsyncTasksManager::start(std::function<void()> task, const std::chrono::milliseconds& ms)
        {
            const auto token = tokensProvider.get();
            auto it = tasks.emplace(token, AsyncTask{ task, ms });
        }

        void AsyncTasksManager::stopAll()
        {
            tasks.clear();
        }

        void AsyncTasksManager::removeTasksFromList(const std::vector<Utils::TokensProvider::Token>& tokens)
        {
            for (const auto token : tokens)
                tasks.erase(token);
        }

    }
}
