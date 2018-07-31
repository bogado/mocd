#ifndef HARDWARE_HPP_INCLUDED
#define HARDWARE_HPP_INCLUDED

#include "type_helper.hpp"

namespace mocd
{

namespace
{
    using namespace mocd::types;
}

namespace details
{

template <typename CONTROLLER>
constexpr auto begin(CONTROLLER& control) noexcept
    -> typename enable_if<has_void_begin_t<CONTROLLER>::value, void>::type
{
    control.begin();
}

template <typename CONTROLLER>
constexpr auto begin(CONTROLLER& control, ...) noexcept
    -> typename enable_if_t<!has_void_begin_t<CONTROLLER>::value, void>::type
{
    // NO OP.
    // All initialization is made on construction.
}

template <typename TYPE>
inline TYPE default_builder() noexcept
{
    TYPE result;
    begin(result);
    return result;
}

}

template <typename TRAITS>
class controller
{
    using traits = TRAITS;
public:
    using driver_type = typename traits::driver_type;

private:
    static driver_type& get_driver() noexcept {
        static driver_type instance = traits::build_and_initialize();

        return instance;
    }

public:
    constexpr driver_type& operator*() noexcept
    {
        return get_driver();
    }

    constexpr driver_type* operator->() noexcept
    {
        return &get_driver();
    }
};

template <typename DRIVER>
class controller_traits
{
public:
    using driver_type = DRIVER;
    using controller_type = controller<controller_traits>;

    constexpr static driver_type build_and_initialize() noexcept
    {
        return details::default_builder<driver_type>();
    }
};

template <
    typename DRIVER,
    typename TRAITS = controller_traits<DRIVER>
>
class device {
public:
    using controller_traits = TRAITS;
    using controller = typename controller_traits::controller_type;
};

}

#endif
