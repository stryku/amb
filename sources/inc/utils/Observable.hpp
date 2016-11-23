#pragma once

namespace Amb
{
    namespace Utils
    {
        template <typename WrappedType>
        class Observable
        {
        public:
            using CallbackType = std::function<void(const WrappedType&)>;

            Observable(CallbackType callback)
                : callback{ callback }
            {}

            void set(const WrappedType &v)
            {
                value = v;
                callback(value);
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