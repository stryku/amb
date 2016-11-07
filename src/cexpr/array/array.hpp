#pragma once

namespace cexpr
{
    template <typename T, size_t N>
    struct array
    {
        constexpr T& operator[](size_t i)
        {
            return arr[i];
        }

        constexpr T* begin()
        {
            return arr;
        }

        constexpr const T* cbegin() const
        {
            return arr;
        }

        constexpr T* end()
        {
            return arr + N;
        }
        constexpr const T* cend() const
        {
            return arr + N;
        }

        T arr[N];
    };
}
