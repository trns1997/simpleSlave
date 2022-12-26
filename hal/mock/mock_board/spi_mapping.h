#ifndef MOCK_SPI_MAPPING_H_
#define MOCK_SPI_MAPPING_H_

#include "stdint.h"

namespace board
{

    typedef enum
    {
        SPI_IMU = 0,
        SPI_FS
    } spi_identifier;

    typedef struct
    {
        spi_identifier name;
    } spi_conf_t;

    static spi_conf_t spi_mapping[] =
    {
        {
            SPI_IMU,
        },
        {
            SPI_FS,
        },
    };

}

#endif
