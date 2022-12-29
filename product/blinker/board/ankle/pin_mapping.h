#ifndef ANKLE_PIN_MAPPING_H_
#define ANKLE_PIN_MAPPING_H_

#include "xmc_gpio.h"
#include "stdint.h"

namespace board
{
    typedef enum
    {
        LED1 = 0,
    } pin_identifier;

    typedef struct
    {
        pin_identifier      pin_id;
        XMC_GPIO_PORT_t*    port;
        uint8_t             pin;
        XMC_GPIO_MODE_t     mode;
    } pin_conf_t;

    static pin_conf_t pin_mapping[] =
    {
        {LED1 ,     XMC_GPIO_PORT5, 8, XMC_GPIO_MODE_OUTPUT_PUSH_PULL},
    };
}
#endif
