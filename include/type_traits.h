// ReSharper disable CppUseTypeTraitAlias
#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#include "stddef.h"

namespace std {
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
    struct is_same : std::false_type {
    };

    template<typename T>
    struct is_same<T, T> : std::true_type {
    };

    template<typename T, typename U>
    inline constexpr bool is_same_v = is_same<T, U>::value;

    template<typename T>
    struct remove_cv {
        typedef T type;
    };

    template<typename T>
    struct remove_cv<const T> {
        typedef T type;
    };

    template<typename T>
    struct remove_cv<volatile T> {
        typedef T type;
    };

    template<typename T>
    struct remove_cv<const volatile T> {
        typedef T type;
    };

    template<typename T>
    using remove_cv_t = typename remove_cv<T>::type;

    template<typename T>
    struct remove_reference {
        typedef T type;
    };

    template<typename T>
    struct remove_reference<T &> {
        typedef T type;
    };

    template<typename T>
    using remove_reference_t = typename remove_reference<T>::type;

    template<bool B, typename T, typename F>
    struct conditional {
        using type = T;
    };

    template<typename T, typename F>
    struct conditional<false, T, F> {
        using type = F;
    };

    template<typename T>
    struct is_array : false_type {
    };

    template<typename T, size_t N>
    struct is_array<T[N]> : true_type {
    };

    template<typename T>
    struct is_array<T[]> : true_type {
    };

    template<typename T>
    struct remove_extent {
        using type = T;
    };

    template<typename T, size_t N>
    struct remove_extent<T[N]> {
        using type = T;
    };

    template<typename T>
    struct remove_extent<T[]> {
        using type = T;
    };

    template<typename T>
    using remove_extent_t = typename remove_extent<T>::type;

    template<typename T>
    struct is_function : std::false_type {
    };

    template<typename R, typename... Args>
    struct is_function<R(Args...)> : std::true_type {
    };

    template<typename R, typename... Args>
    struct is_function<R(Args..., ...)> : std::true_type {
    };

    template<typename T>
    constexpr bool is_function_v = is_function<T>::value;

    template<typename T>
    struct add_pointer {
        using type = typename std::remove_reference<T>::type *;
    };

    template<typename T>
    using add_pointer_t = typename add_pointer<T>::type;

    template<typename T>
    struct decay {
        // 首先移除引用，得到 U 类型
        using U = typename std::remove_reference<T>::type;

        // 如果 U 是数组类型，则转换为对应的指针类型
        // 如果 U 是函数类型，则转换为对应的函数指针类型
        // 否则，移除顶层的 const 和 volatile 限定符
        using type = typename std::conditional<
            std::is_array<U>::value,
            typename std::remove_extent<U>::type *,
            typename std::conditional<
                std::is_function<U>::value,
                typename std::add_pointer<U>::type,
                typename std::remove_cv<U>::type
            >::type
        >::type;
    };

    template<typename T>
    using decay_t = typename std::decay<T>::type;
}

#endif //TYPE_TRAITS_H
