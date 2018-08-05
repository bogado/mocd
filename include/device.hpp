#ifndef HARDWARE_HPP_INCLUDED
#define HARDWARE_HPP_INCLUDED

#include "type_helper.hpp"

#include "details/device.hpp"

/**
 * Give access to the undelying driver class.
 *
 * Responsible for executing all the initializtions on first access.
 */
template <typename TRAITS>
class controller
{
    using traits = TRAITS;
public:
    using driver_type = typename traits::driver_type;

    controller() = default;
    controller(controller&&) = default;
    controller& operator= (controller&&) = default;

    controller(const controller&) = delete;
    controller& operator= (const controller&) = delete;

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

template <typename CONTROLLER>
typename CONTROLLER::driver_type build_and_initialize_driver(CONTROLLER&, ...)
{
    typename CONTROLLER::driver_type value;
    begin(value);
    return value;
}

template <typename T>
constexpr void cleanup_driver(T&, ...)
{
    // NO OP by default.
}

/**
 * Traits to enable customizations on how the controller interact with the driver class.
 */
template <typename DRIVER>
class controller_traits
{
public:
    using driver_type = DRIVER;
    using controller_type = controller<controller_traits>;

    /**
     * Method used to crate and initialize the driver.
     */
    constexpr static driver_type build_and_initialize() noexcept
    {
        return details::default_builder<driver_type>();
    }

    constexpr static void cleanup_driver(driver_type& driver) noexcept
    {
        cleanup_driver(driver);
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
