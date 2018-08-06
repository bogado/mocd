#ifndef DEVICE_HPP_INCLUDED
#define DEVICE_HPP_INCLUDED

namespace mocd
{

namespace details
{

namespace
{
    using namespace mocd::types;
}

/// Executes the method begin, if it exists.
template <typename CONTROLLER>
constexpr auto exec_begin(CONTROLLER& control) noexcept
    -> typename enable_if<has_begin_t<CONTROLLER>::value, void>::type
{
    control.begin();
}

/// This overload is a no op and is used when no begin method exists.
template <typename CONTROLLER>
constexpr auto exec_begin(CONTROLLER& control, ...) noexcept
    -> typename enable_if_t<!has_begin_t<CONTROLLER>::value, void>::type
{
    // NO OP.
    // All initialization is made on construction.
}

/// Default implementation of the build_and_initialize
template <typename TYPE>
inline TYPE default_builder() noexcept
{
    TYPE result;
    exec_begin(result);
    return result;
}

}


#endif
