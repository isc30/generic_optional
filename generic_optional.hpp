#pragma once

#include <optional>
#include <functional>

namespace generic_optional_details
{
    template<typename T>
    using ref_t = std::reference_wrapper<T>;

    template<typename T>
    struct wrapper
    {
        using type = T;
    };

    template<typename T>
    struct wrapper<T&>
    {
        using type = ref_t<T>;
    };

    template<typename T>
    using wrapped_t = typename wrapper<T>::type;

    // small tests
    template<typename T, typename U = T>
    constexpr bool is_same_wrapped_v = std::is_same_v<wrapped_t<T>, U>;

    static_assert(is_same_wrapped_v<int>, "simple type");
    static_assert(is_same_wrapped_v<const int>, "const");
    static_assert(is_same_wrapped_v<int*>, "ptr");
    static_assert(is_same_wrapped_v<const int*>, "ptr to const");
    static_assert(is_same_wrapped_v<int* const>, "const ptr");
    static_assert(is_same_wrapped_v<int[3]>, "static array");
    static_assert(is_same_wrapped_v<int(*)[3]>, "ptr to static array");
    static_assert(is_same_wrapped_v<const int(*const)[3]>, "const ptr to static array of const");

    static_assert(is_same_wrapped_v<int&, ref_t<int>>, "reference");
    static_assert(is_same_wrapped_v<const int&, ref_t<const int>>, "reference to const");
    static_assert(is_same_wrapped_v<int(&)[3], ref_t<int[3]>>, "reference to static array");
    static_assert(is_same_wrapped_v<const int(&)[3], ref_t<const int[3]>>, "reference to static array of const");

    static_assert(is_same_wrapped_v<int&&, int&&>, "rvalue shouldn't be wrapped");
}

template<typename T>
using generic_optional = std::optional<generic_optional_details::wrapped_t<T>>;
