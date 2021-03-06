#pragma once

#include <functional>

namespace Amb
{
    namespace Utils
    {
        template <typename WrappedType>
        class Observable
        {
        public:
            using CallbackParameterType = const WrappedType&;
            using CallbackType = std::function<void(CallbackParameterType)>;

            Observable() = default;

            Observable(CallbackType callback)
                : callback{ callback }
            {}

            void setCallback(CallbackType cb)
            {
                callback = cb;
            }

            void set(const WrappedType &v)
            {
                if (value != v)
                {
                    value = v;

                    if (callback)
                        callback(value);
                }
            }

            WrappedType get() const
            {
                return value;
            }

        private:
            WrappedType value;
            CallbackType callback;
        };
    }
}