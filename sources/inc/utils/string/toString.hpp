#pragma once

#include "utils/traits/traits.hpp"
#include "utils/traits/TemplateInfo.hpp"

#include <string>

namespace utils // todo Amb::Utils
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

    template <typename ...Args>
    auto toStringArray(const Args&... args)
    {
        return std::array<std::string, Amb::Traits::TemplateArgs<Args...>::count> { toString(args)... };
    }
}
