#include "XMC_Slave.h"

void XMC_Slave::setSPI(XMC_SPI &spi)
{
    spi_ = spi;
}

std::vector<uint8_t> XMC_Slave::getRawData()
{
    return spi_.getRxData();
}

bool XMC_Slave::dataReady()
{
    return spi_.transferStatus();
}

void XMC_Slave::irqHandler()
{
    spi_.interruptCallBack();
}
