// ReSharper disable CppUseTypeTraitAlias
#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

namespace std{
    template<typename Tp, Tp v>
    struct integral_constant {
        static constexpr Tp value = v;
        using value_type = Tp;
        using type = integral_constant;
        explicit constexpr operator value_type() const noexcept { return value; }
    };

    template<bool v>
    using bool_constant = integral_constant<bool, v>;

    using true_type = bool_constant<true>;
    using false_type = bool_constant<false>;

    template<typename T, typename U>
    struct is_same : std::false_type {};

    template<typename T>
    struct is_same<T,T> : std::true_type {};

    template<typename T, typename U>
    inline constexpr bool is_same_v = is_same<T, U>::value;
}

#endif //TYPE_TRAITS_H
