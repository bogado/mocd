#ifndef OUTPUT_PIN_HPP_INCLUDED
#define OUTPUT_PIN_HPP_INCLUDED

#include <Arduino.h>

#include "type_helper.hpp"

namespace mocd
{

namespace
{
    using namespace mocd::types;
}


template <unsigned pin>
class digital_out_pin_driver
{
public:
    void set()
    {
        digitalWrite(pin, HIGH);
    }

    void reset()
    {
        digitalWrite(pin, LOW);
    }

    template <
        typename T,
        typename = enable_if_t<is_convertible_t<T, bool>::value>
    >
    void operator=(T value)
    {
        if (value) {
            set();
        } else {
            reset();
        }
    }
};

}

#endif
