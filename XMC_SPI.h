#ifndef XMC_SPI_H_
#define XMC_SPI_H_

extern "C"
{
#include "xmc_spi.h"
#include "xmc_gpio.h"
}
#include <vector>

struct PIN_CONFIG
{
    XMC_GPIO_PORT_t *port;
    uint8_t pin;
    XMC_GPIO_MODE_t mode;
};

struct SPI_CONFIG
{
    XMC_USIC_CH_t *channel;
    XMC_SPI_CH_CONFIG_t channelConfig;
    XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_t clockPassiveLevel;
    XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_t shiftClockOutput;
    uint32_t txFIFOServiceRequest;
    uint32_t rxFIFOServiceRequest;
    IRQn_Type txIRQ;
    IRQn_Type rxIRQ;
    uint8_t inputSource;
    PIN_CONFIG MOSI;
    PIN_CONFIG MISO;
    PIN_CONFIG SCLK;
    PIN_CONFIG SS;
};

class XMC_SPI
{
public:
    XMC_SPI() = default;
    ~XMC_SPI() = default;

    void init(SPI_CONFIG config);
    void sendData(std::vector<uint8_t> txData, bool blockingMode = false);
    XMC_USIC_CH_t *getChannel();
    void interruptCallBack();
    std::vector<uint8_t> getRxData();
    bool transferStatus();

private:
    XMC_USIC_CH_t *channel_;
    std::vector<uint8_t> txData_;
    std::vector<uint8_t> rxData_;
    bool transferComplete_;
};

#endif
