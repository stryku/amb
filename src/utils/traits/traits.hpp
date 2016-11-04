#pragma once

#include <type_traits>


namespace utils
{
    namespace traits
    {
        template<typename, typename T>
        struct hasToString {
            static constexpr bool value = false;
        };

        template<typename C, typename Ret, typename... Args>
        struct hasToString<C, Ret(Args...)> {
        private:
            template<typename T>
            static constexpr auto check(T*) -> typename std::is_same<decltype(std::declval<T>().toString(std::declval<Args>()...)),
                                                                     Ret>::type;

            template<typename>
            static constexpr std::false_type check(...);

            typedef decltype(check<C>(0)) type;

        public:
            static constexpr bool value = type::value;
        };

        template <typename T>
        struct canCallStdToString
        {
            static constexpr bool value = !std::is_same<T, bool>::value &&
                                          (std::is_integral<T>::value || 
                                           std::is_unsigned<T>::value || 
                                           std::is_floating_point<T>::value);
        };

        template<bool...> struct bool_pack;

        template <bool ...bs>
        using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;

        template <bool ...bs>
        using all_false = std::is_same<bool_pack<bs..., false>, bool_pack<false, bs...>>;

        template <bool ...bs>
        using any_true = std::integral_constant<bool, !all_false<bs...>::value>;

        template <typename T, typename ...Args>
        using is_any_of = any_true<std::is_same<T, Args>::value...>;

        template <typename T, typename ...Args>
        constexpr bool is_any_of_v = is_any_of<T, Args...>::value;
    }
}