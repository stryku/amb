#pragma once

#include "log/condition/LoggerCondition.hpp"

namespace Amb
{
    namespace Log
    {
        namespace Condition
        {
            template <typename WrappedType>
            class LogDifferentThanLastCondition : public LoggerCondition<LogDifferentThanLastCondition<WrappedType>, WrappedType>
            {
            public:
                bool shouldLogDerived(const WrappedType& obj) const
                {
                    return obj != lastLogged;
                }
                void willLogThis(const WrappedType& obj) override
                {
                    lastLogged = obj;
                }

            private:
                WrappedType lastLogged;
            };
        }
    }
}
