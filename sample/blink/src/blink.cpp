#include "device.hpp"
#include "pin.hpp"

using namespace mocd;

using red   = device<digital_out_pin_driver<3>>;
using green = device<digital_out_pin_driver<5>>;
using blue  = device<digital_out_pin_driver<6>>;

void setup() {}

void loop()
{
    red::controller   r;
    green::controller g;
    blue::controller  b;

    r->set();
    delay(1000);
    g->set();
    delay(1000);
    b->set();
    delay(1000);
    r->reset();
    g->reset();
    b->reset();
    delay(1000);
}
