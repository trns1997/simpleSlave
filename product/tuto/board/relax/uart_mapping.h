#ifndef RELAX_UART_MAPPING_H_
#define RELAX_UART_MAPPING_H_

#include "stdint.h"
#include "xmc_uart.h"

namespace board
{

    static XMC_UART_CH_CONFIG_t uart_config =
        {
            .baudrate = 460800U,
            .data_bits = 8U,
            .stop_bits = 1U};

    typedef enum
    {
        UART = 0
    } uart_identifier;

    typedef struct
    {
        uart_identifier name;
        XMC_USIC_CH_t *channel;
        XMC_UART_CH_CONFIG_t channelConfig;
        uint8_t inputSource;
    } uart_conf_t;

    static uart_conf_t uart_mapping[] =
        {
            {UART,
             XMC_UART0_CH0,
             uart_config,
             USIC0_C0_DX0_P1_4},
    };

}

#endif
