#include "GPIO.h"
#include "xmc_gpio.h"

void GPIO::init()
{
	XMC_GPIO_CONFIG_t config;
	if (default_)
	{
		config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH};
	}
	else
	{
		config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL, .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW};
	}
	XMC_GPIO_Init(port_, pin_, &config);
}

bool GPIO::getPin()
{
	uint32_t val = XMC_GPIO_GetInput(port_, pin_);
	return static_cast<bool>(val);
}

void GPIO::setPin()
{
	XMC_GPIO_SetOutputHigh(port_, pin_);
}

void GPIO::resetPin()
{
	XMC_GPIO_SetOutputLow(port_, pin_);
}

void GPIO::togglePin()
{
	XMC_GPIO_ToggleOutput(port_, pin_);
}
