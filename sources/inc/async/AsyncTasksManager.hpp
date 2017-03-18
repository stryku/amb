#pragma once

#include "utils/TokensProvider.hpp"
#include "async/AsyncTask.hpp"

#include <functional>
#include <chrono>
#include <unordered_map>

namespace Amb
{
    namespace Async
    {
        class AsyncTasksManager
        {
        public:
            void tick();
            void start(std::function<void()> task, const std::chrono::milliseconds& ms);
            void stopAll();

        private:
            void removeTasksFromList(const std::vector<Utils::TokensProvider::Token>& tokens);

            Utils::TokensProvider tokensProvider;
            std::unordered_map<Utils::TokensProvider::Token, AsyncTask> tasks;
        };
    }
}
