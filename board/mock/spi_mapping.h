#ifndef MOCK_SPI_MAPPING_H_
#define MOCK_SPI_MAPPING_H_

#include "stdint.h"

namespace board
{

    typedef enum
    {
        SPI0_CH1 = 0,
        SPI1_CH0,
        SPI2_CH0
    } spi_identifier;

    typedef struct
    {
        spi_identifier name;
    } spi_conf_t;

    static spi_conf_t spi_mapping[] =
    {
        {
            SPI0_CH1,
        },
        {
            SPI1_CH0,
        },
        {
            SPI2_CH0,
        },
    };

}

#endif
