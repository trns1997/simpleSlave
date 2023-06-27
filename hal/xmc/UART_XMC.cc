#include "UART.h"
#include "xmc_uart.h"

using namespace board;

void UART::init()
{
    XMC_UART_CH_Init(uart_conf_.channel, &uart_conf_.channelConfig);
    XMC_UART_CH_SetInputSource(uart_conf_.channel, XMC_UART_CH_INPUT_RXD, uart_conf_.inputSource);
    XMC_UART_CH_Start(uart_conf_.channel);
}

void UART::sendData(uint8_t *txData, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        XMC_UART_CH_Transmit(uart_conf_.channel, txData[i]);
    }
}
