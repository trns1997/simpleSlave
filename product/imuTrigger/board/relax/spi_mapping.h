#ifndef RELAX_SPI_MAPPING_H_
#define RELAX_SPI_MAPPING_H_

#include "stdint.h"
#include "xmc_spi.h"

#define SPI_Force_Sensor_RX_Interrupt USIC0_2_IRQHandler
#define SPI_Force_Sensor_TX_Interrupt USIC0_3_IRQHandler
#define SPI_IMU_RX_Interrupt USIC2_2_IRQHandler
#define SPI_IMU_TX_Interrupt USIC2_3_IRQHandler

namespace board
{

    static XMC_SPI_CH_CONFIG_t spi_config =
        {
            .baudrate = 800000,
            .bus_mode = XMC_SPI_CH_BUS_MODE_MASTER,
            .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
            .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE};

    typedef enum
    {
        SPI_IMU = 0
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
            {SPI_IMU,
             XMC_SPI2_CH0,
             spi_config,
             XMC_SPI_CH_SLAVE_SELECT_0,
             XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_DISABLED,
             XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK,
             3,
             2,
             USIC2_3_IRQn,
             USIC2_2_IRQn,
             USIC2_C0_DX0_P3_7},
    };

}

#endif
