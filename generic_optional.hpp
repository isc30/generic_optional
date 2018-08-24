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
}

template<typename T>
using generic_optional = std::optional<generic_optional_details::wrapped_t<T>>;
