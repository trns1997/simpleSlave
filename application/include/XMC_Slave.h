#ifndef XMC_Slave_H_
#define XMC_Slave_H_

#include <vector>
#include <memory>
#include "XMC_SPI.h"
#include "xmc_spi.h"
#include "xmc_gpio.h"

class XMC_Slave
{
public:
    XMC_Slave() = default;
    ~XMC_Slave() = default;

    void setSPI(XMC_SPI &spi);
    virtual void configure() = 0;
    virtual void read() = 0;
    std::vector<uint8_t> getRawData();
    bool dataReady();
    void irqHandler();

protected:
    XMC_SPI spi_;
};

#endif
