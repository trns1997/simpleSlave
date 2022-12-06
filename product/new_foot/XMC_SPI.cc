#include "XMC_SPI.h"

void XMC_SPI::init(SPI_CONFIG config)
{
    channel_ = config.channel;
    XMC_SPI_CH_Init(channel_, &config.channelConfig);
    XMC_SPI_CH_SetBitOrderMsbFirst(channel_);
    XMC_SPI_CH_SetWordLength(channel_, (uint8_t)8);
    /* Configure the clock polarity and clock delay */
    XMC_SPI_CH_ConfigureShiftClockOutput(channel_,
                                         config.clockPassiveLevel,
                                         config.shiftClockOutput);
    /* Configure Leading/Trailing delay */
    XMC_SPI_CH_SetSlaveSelectDelay(channel_, 2U);

    /* Configure transmit FIFO settings */
    XMC_USIC_CH_TXFIFO_Configure(channel_,
                                 16U,
                                 (XMC_USIC_CH_FIFO_SIZE_t)XMC_USIC_CH_FIFO_SIZE_16WORDS,
                                 1U);

    /* Configure receive FIFO settings */
    XMC_USIC_CH_RXFIFO_Configure(channel_,
                                 0U,
                                 (XMC_USIC_CH_FIFO_SIZE_t)XMC_USIC_CH_FIFO_SIZE_16WORDS,
                                 0U);

    /* Configure the service interrupt nodes for standard transmit FIFO events */
    XMC_USIC_CH_TXFIFO_SetInterruptNodePointer(channel_,
                                               XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD,
                                               config.txFIFOServiceRequest);
    /* Configure the service interrupt nodes for standard receive FIFO events */
    XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(channel_,
                                               XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD,
                                               config.rxFIFOServiceRequest);
    // /* Enable Transmit and Receive interrupt */
    NVIC_ClearPendingIRQ(config.txIRQ);
    NVIC_ClearPendingIRQ(config.rxIRQ);
    NVIC_SetPriority(config.txIRQ, 10U);
    NVIC_SetPriority(config.rxIRQ, 10U);
    NVIC_EnableIRQ(config.txIRQ);
    NVIC_EnableIRQ(config.rxIRQ);

    /*Input source selected*/
    XMC_SPI_CH_SetInputSource(channel_, XMC_SPI_CH_INPUT_DIN0, config.inputSource);
    XMC_SPI_CH_Start(channel_);
}

void XMC_SPI::sendData(std::vector<uint8_t> txData, bool blockingMode)
{
    txData_ = txData;
    transferComplete_ = false;
    XMC_SPI_CH_EnableSlaveSelect(channel_, XMC_SPI_CH_SLAVE_SELECT_0);
    /* Flush the Receive FIFO */
    XMC_USIC_CH_RXFIFO_Flush(channel_);
    /* Set Trigger Limit for the RXFIFO for when to trigger interrupt */
    XMC_USIC_CH_RXFIFO_SetSizeTriggerLimit(channel_, XMC_USIC_CH_FIFO_SIZE_16WORDS, txData.size() - 1);
    XMC_USIC_CH_RXFIFO_EnableEvent(channel_, XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD);

    /* Flush the Transmit FIFO */
    XMC_USIC_CH_TXFIFO_Flush(channel_);
    XMC_USIC_CH_TXFIFO_EnableEvent(channel_, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);

    for (const uint8_t &data : txData)
    {
        XMC_USIC_CH_TXFIFO_PutDataHPCMode(channel_, data, XMC_SPI_CH_MODE_STANDARD);
    }
    XMC_USIC_CH_TXFIFO_DisableEvent(channel_, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);

    while (blockingMode and not transferComplete_)
    {
    }
}

XMC_USIC_CH_t *XMC_SPI::getChannel()
{
    return channel_;
}

void XMC_SPI::interruptCallBack()
{
    rxData_.clear();
    for (uint16_t i = 0; i < txData_.size(); i++)
    {
        rxData_.push_back(XMC_SPI_CH_GetReceivedData(channel_));
    }
    XMC_USIC_CH_RXFIFO_DisableEvent(channel_, (uint32_t)XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD |
                                                  (uint32_t)XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE);

    XMC_SPI_CH_DisableSlaveSelect(channel_);
    transferComplete_ = true;
}

std::vector<uint8_t> XMC_SPI::getRxData()
{
    return rxData_;
}

bool XMC_SPI::transferStatus()
{
    return transferComplete_;
}
