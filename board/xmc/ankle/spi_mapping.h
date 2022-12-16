#ifndef ANKLE_SPI_MAPPING_H_
#define ANKLE_SPI_MAPPING_H_

#include "xmc_spi.h"
#include "stdint.h"

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
        SPI0_CH1 = 0,
        SPI2_CH0
    } spi_identifier;

    typedef struct
    {
        spi_identifier name;
        XMC_USIC_CH_t *channel;
        XMC_SPI_CH_CONFIG_t channelConfig;
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
            {SPI0_CH1,
             XMC_SPI0_CH1,
             spi_config,
             XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_DISABLED,
             XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK,
             3,
             2,
             USIC0_3_IRQn,
             USIC0_2_IRQn,
             USIC0_C1_DX0_P2_2},
            {SPI2_CH0,
             XMC_SPI2_CH0,
             spi_config,
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