#ifndef HAL_INC_GPIO_H_
#define HAL_INC_GPIO_H_

#include <stdint.h>
#include "pin_mapping.h"

class GPIO
{

public:
	GPIO(board::pin_identifier pin_name): pin_conf_(board::pin_mapping[pin_name])
	{}
	~GPIO() {}
	GPIO(const GPIO&) = delete;
	GPIO& operator = (const GPIO&) = delete;

	void init();

	bool getPin();
	void setPin();
	void resetPin();
	void togglePin();

private:
	board::pin_conf_t pin_conf_;
};


static void initGPIO()
{
	for (int i = 0; i < (sizeof(board::pin_mapping)/sizeof(board::pin_conf_t)); i++)
	{
		GPIO gpio(static_cast<board::pin_identifier>(i));
		gpio.init();
	}
}

#endif /* HAL_INC_IGPIO_H_ */
