#pragma once

#include "utils.hpp"

#include <thread>
#include <chrono>

namespace Amb
{
    namespace Utils
    {
        class ThreadWorker
        {
        public:
            ~ThreadWorker();

            template <typename LoopFunction>
            void start(LoopFunction loopFunction, Utils::RandomBetween sleepDuration)
            {
                stop();

                auto loop = [this, loopFunction, sleepDuration]()
                {
                    while (needRunning)
                    {
                        const auto sleepTo = std::chrono::system_clock::now() +
                                             std::chrono::milliseconds(sleepDuration.get());

                        loopFunction();

                        std::this_thread::sleep_until(sleepTo);
                    }
                };

                needRunning = true;

                thread = std::thread{ loop };
            }

            template <typename LoopFunction, typename Rep, typename Period>
            void start(LoopFunction loopFunction, const std::chrono::duration<Rep, Period> &duration)
            {
                stop();

                auto loop = [this, loopFunction, duration]()
                {
                    while (needRunning)
                    {
                        const auto sleepTo = std::chrono::system_clock::now() + duration;

                        loopFunction();

                        std::this_thread::sleep_until(sleepTo);
                    }
                };

                needRunning = true;

                thread = std::thread{ loop };
            }

            void stop();

        private:
            std::thread thread;
            bool needRunning{ false };
        };
    }
}
