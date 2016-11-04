#pragma once

#include <utils/traits/traits.hpp>

#include <string>

namespace utils
{
    template <typename T>
    typename std::enable_if_t<std::is_convertible<T, std::string>::value, std::string>
        toString(const T &value)
    {
        return{ value };
    }

    template <typename T>
    typename std::enable_if_t<traits::canCallStdToString<T>::value, std::string>
        toString(const T &value)
    {
        return std::to_string(value);
    }

    template <typename T>
    typename std::enable_if_t<traits::hasToString<T, std::string()const>::value, std::string>
        toString(const T &value)
    {
        return value.toString();
    }

    std::string toString(bool value);
}
