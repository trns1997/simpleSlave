#ifndef RELAX_SPI_MAPPING_H_
#define RELAX_SPI_MAPPING_H_

#include "xmc_spi.h"
#include "stdint.h"

namespace board
{
    typedef enum
    {
        SPI_FS = 0,
        SPI1_CH0,
        SPI_IMU
    } spi_identifier;

    typedef struct
    {
        spi_identifier name;
        XMC_USIC_CH_t *channel;
        XMC_SPI_CH_CONFIG_t channelConfig;
        XMC_SPI_CH_SLAVE_SELECT_t chipSelect;
        XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_t clockPassiveLevel;
        XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_t shiftClockOutput;
        uint32_t txFIFOServiceRequest;
        uint32_t rxFIFOServiceRequest;
        IRQn_Type txIRQ;
        IRQn_Type rxIRQ;
        uint8_t inputSource;
    } spi_conf_t;

    static spi_conf_t spi_mapping[] =
    {
    };

}

#endif
