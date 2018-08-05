# MOCD -- A Modern C++ adaptor for Arduino.

This is a library to make Arduino development closer to the usual C++ way of thinking.

## RAII

The main objective is to enable "pseudo-RAII" for many of the arduino libraries that drives different elements. Most of them expect you to follow the following pattern :

```C++
#include "my_hardware.hpp"

// Connected to pin 2
my_hardware_type my_device;

void setup()
{
    my_device.begin(2);
}

void loop()
{
    delay(1000);
    my_device.make_magic();
}
```

To something like this :

```C++
using my_device = mocd::device<magic_driver<2>>;

void setup() { /* Nothig expected here */ }

void loop()
{
    my_device::controller test;

    test->make_magic()
}
```

This may make the first run of the loop have slightly different timings than the normal run, but this is something I'm willing to live with.
