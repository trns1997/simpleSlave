#ifndef RELAX_PIN_MAPPING_H_
#define RELAX_PIN_MAPPING_H_

#include "stdint.h"
#include "xmc_gpio.h"

namespace board
{
    typedef enum
    {
        LED1 = 0,
        SPI2_CH0_MOSI,
        SPI2_CH0_MISO,
        SPI2_CH0_CLK,
        SPI2_CH0_CS1
    } pin_identifier;

    typedef struct
    {
        pin_identifier pin_id;
        XMC_GPIO_PORT_t *port;
        uint8_t pin;
        XMC_GPIO_MODE_t mode;
    } pin_conf_t;

    static pin_conf_t pin_mapping[] =
        {
            {LED1, XMC_GPIO_PORT5, 8, XMC_GPIO_MODE_OUTPUT_PUSH_PULL},

            {SPI2_CH0_MOSI, XMC_GPIO_PORT3, 8, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1},
            {SPI2_CH0_MISO, XMC_GPIO_PORT3, 7, XMC_GPIO_MODE_INPUT_TRISTATE},
            {SPI2_CH0_CLK, XMC_GPIO_PORT3, 9, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1},
            {SPI2_CH0_CS1, XMC_GPIO_PORT3, 10, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1},
    };
}

#endif
