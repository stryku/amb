#pragma once

namespace Amb
{
    namespace Traits
    {
#if __cplusplus <= 199711L
        namespace detail
        {
            template<typename... Args> struct count;

            template<>
            struct count<> {
                static const int value = 0;
            };

            template<typename T, typename... Args>
            struct count<T, Args...> {
                static const int value = 1 + count<Args...>::value;
            };
        }

        template <typename ...T>
        struct TemplateArgs
        {
            static const size_t count = detail::count<T...>::value;
        };
#else
        template <typename ...T>
        struct TemplateArgs
        {
            constexpr size_t count = sizeof...(T);
        };
#endif
    }
}