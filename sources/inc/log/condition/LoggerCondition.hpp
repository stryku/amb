#pragma once

#include <utility>

namespace Amb
{
    namespace Log
    {
        namespace Condition
        {
            template <typename DerivedCondition, typename ...Args>
            class LoggerCondition
            {
            public:
                bool shouldLog(const Args&... args) const
                {
                    return externalBool && 
                           static_cast<DerivedCondition>(this)->shouldLogDerived(std::forward<Args>(args)...);
                }

                void setExternalBool(bool cond) 
                { 
                    externalBool = cond;
                }

                virtual void willLogThis(const Args&... args) = 0;

            protected:
                bool externalBool{ true };
            };
        }
    }
}
