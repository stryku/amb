#pragma once

namespace Amb
{
    namespace Utils
    {
        template <typename WrappedType, typename Observer>
        class Observable
        {
        public:
            Observable(Observer &observer)
                : observer{ observer }
            {}

            void set(const WrappedType &v)
            {
                value = v;
                observer.notifyChanged(value);
            }

            WrappedType get() const
            {
                return value;
            }

        private:
            WrappedType value;
            Observer &observer;
        };
    }
}