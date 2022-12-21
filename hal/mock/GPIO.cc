#include "GPIO.h"

using namespace board;

static bool pin_value {false};

void GPIO::init()
{
    pin_value = false;
}

bool GPIO::getPin()
{
    return pin_value;
}

void GPIO::setPin()
{
    pin_value = true;
}

void GPIO::resetPin()
{
    pin_value = false;
}

void GPIO::togglePin()
{
	pin_value = !pin_value;
}
