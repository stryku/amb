#pragma once

#include "cexpr/array.hpp"

namespace cexpr
{
    namespace detail
    {
        template<class T>
        constexpr void swap(T& l, T& r)
        {
            T tmp = std::move(l);
            l = std::move(r);
            r = std::move(tmp);
        }

        template <typename T, size_t N>
        constexpr void sort(array<T, N> &array, size_t left, size_t right)
        {
            if (left < right)
            {
                size_t m = left;

                for (size_t i = left + 1; i<right; i++)
                    if (array[i]<array[left])
                        swap(array[++m], array[i]);

                swap(array[left], array[m]);

                sort(array, left, m);
                sort(array, m + 1, right);
            }
        }

        template <typename T, size_t N>
        constexpr size_t binary_search(const array<T, N>& array, const T& value)
        {
            size_t left{ 0 };
            size_t right{ N - 1 };
            size_t mid;

            while (left <= right)
            {
                mid = (left + right) / 2;

                if (value == array[mid])
                    return mid;
                else if (value > array[mid])
                    left = mid + 1;
                else
                    right = mid - 1;
            }

            return -1;
        }
    }
}
