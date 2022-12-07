#include "GPIO.h"
#include "xmc_gpio.h"

using namespace board;

void GPIO::init()
{
	XMC_GPIO_CONFIG_t config = {.mode = pin_conf_.mode};
	XMC_GPIO_Init(pin_conf_.port, pin_conf_.pin, &config);
}

bool GPIO::getPin()
{
	uint32_t val = XMC_GPIO_GetInput(pin_conf_.port, pin_conf_.pin);
	return static_cast<bool>(val);
}

void GPIO::setPin()
{
	XMC_GPIO_SetOutputHigh(pin_conf_.port, pin_conf_.pin);
}

void GPIO::resetPin()
{
	XMC_GPIO_SetOutputLow(pin_conf_.port, pin_conf_.pin);
}

void GPIO::togglePin()
{
	XMC_GPIO_ToggleOutput(pin_conf_.port, pin_conf_.pin);
}
