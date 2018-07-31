#ifndef TYPE_HELPER_HPP_INCLUDED
#define TYPE_HELPER_HPP_INCLUDED

/*
 * This are some types that are usually defined on type_traits.
 *
 * Unfortunatelly not all toolchains have the whole std defined.
 *
 * ATTENTION: This implementations are quick and dirty and might not be 100%
 * compatible with the same-named concepts on the standard.
 */

namespace mocd {
namespace types {

template <bool CONDITION, typename T>
struct enable_if {};

template <typename T>
struct enable_if<true, T>
{
    using type = T;
};

template <bool CONDITION, typename T = void>
using enable_if_t = enable_if<CONDITION, T>;

template <typename T>
using begin_result = decltype(((T*)(0))->begin());

template <typename T, typename V = void>
struct has_void_begin
{
    static constexpr bool value = false;
};

template <typename T>
struct has_void_begin<T, begin_result<T>>
{
    static constexpr bool value = true;
    using type = begin_result<T>;
};

template<typename T>
using has_void_begin_t = has_void_begin<T>;

template <typename CONTROLLER>
constexpr begin_result<CONTROLLER> begin(CONTROLLER & control) noexcept
{
    return control.begin();
}

template <typename T, typename V, typename TEST = void>
struct is_convertible
{
    static constexpr bool value = false;
};

template <typename T, typename V>
struct is_convertible<T, V, decltype((T*)(0) == (V*)(0))>
{
    static constexpr bool value = true;
};

template <typename T, typename V>
using is_convertible_t = is_convertible<T, V>;

}
}

#endif
