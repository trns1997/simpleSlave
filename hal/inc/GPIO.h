#ifndef HAL_INC_GPIO_H_
#define HAL_INC_GPIO_H_

#include <stdint.h>

class GPIO
{

public:
	GPIO(void* port, uint8_t pin, bool value = false):
		port_(port),
		pin_(pin),
		default_(value)
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
	void* port_ {0};
	uint8_t pin_ {0};
	bool default_ {false};
};


#endif /* HAL_INC_IGPIO_H_ */
