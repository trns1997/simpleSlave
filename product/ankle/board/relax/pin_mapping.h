#ifndef RELAX_PIN_MAPPING_H_
#define RELAX_PIN_MAPPING_H_

#include "xmc_gpio.h"
#include "stdint.h"

namespace board
{
    typedef enum
    {
        LED1 = 0,
        LED2,
        SPI0_CH1_MOSI,
        SPI0_CH1_MISO,
        SPI0_CH1_CLK,
        SPI0_CH1_CS1,
        SPI2_CH0_MOSI,
        SPI2_CH0_MISO,
        SPI2_CH0_CLK,
        SPI2_CH0_CS1
    } pin_identifier;

    typedef struct
    {
        pin_identifier 		pin_id;
        XMC_GPIO_PORT_t* 	port;
        uint8_t				pin;
        XMC_GPIO_MODE_t 	mode;
    } pin_conf_t;

    static pin_conf_t pin_mapping[] =
    {
        {LED1 , 	XMC_GPIO_PORT5, 8, XMC_GPIO_MODE_OUTPUT_PUSH_PULL},
        {LED2 , 	XMC_GPIO_PORT5, 9, XMC_GPIO_MODE_OUTPUT_PUSH_PULL},

        {SPI0_CH1_MOSI, XMC_GPIO_PORT2, 5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2},
        {SPI0_CH1_MISO, XMC_GPIO_PORT2, 2, XMC_GPIO_MODE_INPUT_TRISTATE},
        {SPI0_CH1_CLK,  XMC_GPIO_PORT2, 4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2},
        {SPI0_CH1_CS1, 	XMC_GPIO_PORT2, 3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2},

        {SPI2_CH0_MOSI, XMC_GPIO_PORT3, 8, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1},
        {SPI2_CH0_MISO, XMC_GPIO_PORT3, 7, XMC_GPIO_MODE_INPUT_TRISTATE},
        {SPI2_CH0_CLK,  XMC_GPIO_PORT3, 9, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1},
        {SPI2_CH0_CS1, 	XMC_GPIO_PORT3,10, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1},
    };
}


#endif
