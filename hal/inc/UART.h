#ifndef HAL_INC_UART_H_
#define HAL_INC_UART_H_

#include "uart_mapping.h"
#include <stdint.h>

class UART
{
public:
	UART(board::uart_identifier uart_name) : uart_conf_(board::uart_mapping[uart_name])
	{
	}
	~UART() {}

	void init();

	void sendData(uint8_t *txData, uint32_t size);

private:
	board::uart_conf_t uart_conf_;
};

static void initUART()
{
	for (int i = 0; i < (sizeof(board::uart_mapping) / sizeof(board::uart_conf_t)); i++)
	{
		UART uart(static_cast<board::uart_identifier>(i));
		uart.init();
	}
}

#endif
