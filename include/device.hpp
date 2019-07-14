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

    ~controller()
    {
        cleanup_driver(get_driver());
    }

private:
    static driver_type& get_driver() noexcept
    {
        static driver_type instance = traits::build_and_initialize();

        return instance;
    }

public:
    driver_type& operator*() noexcept
    {
        return get_driver();
    }

    driver_type* operator->() noexcept
    {
        return &get_driver();
    }
};

template <typename DRIVER>
DRIVER build_and_initialize_driver()
{
    DRIVER value;
    details::exec_begin(value);
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
    static driver_type build_and_initialize() noexcept
    {
        return build_and_initialize_driver(static_cast<driver_type*>(nullptr));
    }

    static void cleanup_driver(driver_type& driver) noexcept
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
