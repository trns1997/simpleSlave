#include "SPI.h"
#include "xmc_spi.h"

#include <memory>



void SPI::init()
{
    XMC_SPI_CH_Init(spi_conf_.channel, &spi_conf_.channelConfig);
    XMC_SPI_CH_SetBitOrderMsbFirst(spi_conf_.channel);
    XMC_SPI_CH_SetWordLength(spi_conf_.channel, (uint8_t)8);
    /* Configure the clock polarity and clock delay */
    XMC_SPI_CH_ConfigureShiftClockOutput(spi_conf_.channel,
                                         spi_conf_.clockPassiveLevel,
                                         spi_conf_.shiftClockOutput);
    /* Configure Leading/Trailing delay */
    XMC_SPI_CH_SetSlaveSelectDelay(spi_conf_.channel, 2U);

    /* Configure transmit FIFO settings */
    XMC_USIC_CH_TXFIFO_Configure(spi_conf_.channel,
                                 16U,
                                 (XMC_USIC_CH_FIFO_SIZE_t)XMC_USIC_CH_FIFO_SIZE_16WORDS,
                                 1U);

    /* Configure receive FIFO settings */
    XMC_USIC_CH_RXFIFO_Configure(spi_conf_.channel,
                                 0U,
                                 (XMC_USIC_CH_FIFO_SIZE_t)XMC_USIC_CH_FIFO_SIZE_16WORDS,
                                 0U);

    /* Configure the service interrupt nodes for standard transmit FIFO events */
    XMC_USIC_CH_TXFIFO_SetInterruptNodePointer(spi_conf_.channel,
                                               XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD,
                                               spi_conf_.txFIFOServiceRequest);
    /* Configure the service interrupt nodes for standard receive FIFO events */
    XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(spi_conf_.channel,
                                               XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD,
                                               spi_conf_.rxFIFOServiceRequest);
    // /* Enable Transmit and Receive interrupt */
    NVIC_ClearPendingIRQ(spi_conf_.txIRQ);
    NVIC_ClearPendingIRQ(spi_conf_.rxIRQ);
    NVIC_SetPriority(spi_conf_.txIRQ, 10U);
    NVIC_SetPriority(spi_conf_.rxIRQ, 10U);
    NVIC_EnableIRQ(spi_conf_.txIRQ);
    NVIC_EnableIRQ(spi_conf_.rxIRQ);

    /*Input source selected*/
    XMC_SPI_CH_SetInputSource(spi_conf_.channel, XMC_SPI_CH_INPUT_DIN0, spi_conf_.inputSource);
    XMC_SPI_CH_Start(spi_conf_.channel);
}

void SPI::sendData(uint8_t* txData, uint32_t size)
{
    transferComplete_ = false;
    XMC_SPI_CH_EnableSlaveSelect(spi_conf_.channel, XMC_SPI_CH_SLAVE_SELECT_0);
    /* Flush the Receive FIFO */
    XMC_USIC_CH_RXFIFO_Flush(spi_conf_.channel);
    /* Set Trigger Limit for the RXFIFO for when to trigger interrupt */
    XMC_USIC_CH_RXFIFO_SetSizeTriggerLimit(spi_conf_.channel, XMC_USIC_CH_FIFO_SIZE_16WORDS, size - 1);
    XMC_USIC_CH_RXFIFO_EnableEvent(spi_conf_.channel, XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD);

    /* Flush the Transmit FIFO */
    XMC_USIC_CH_TXFIFO_Flush(spi_conf_.channel);
    XMC_USIC_CH_TXFIFO_EnableEvent(spi_conf_.channel, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);

    for (uint8_t i = 0 ; i < size ; i++)
    {
        XMC_USIC_CH_TXFIFO_PutDataHPCMode(spi_conf_.channel, txData[i], XMC_SPI_CH_MODE_STANDARD);
    }
    XMC_USIC_CH_TXFIFO_DisableEvent(spi_conf_.channel, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);

    while(not transferComplete_)
    {}
}

void SPI::readData(uint8_t* rxData, uint32_t& size)
{
    for (uint16_t i = 0; i < size; i++)
    {
        rxData[i] = XMC_SPI_CH_GetReceivedData(spi_conf_.channel);
    }
    XMC_USIC_CH_RXFIFO_DisableEvent(spi_conf_.channel,
                                    (uint32_t)XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD |
                                    (uint32_t)XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE);

    XMC_SPI_CH_DisableSlaveSelect(spi_conf_.channel);
    transferComplete_ = true;
}
