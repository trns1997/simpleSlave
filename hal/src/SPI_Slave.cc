#include "SPI_Slave.h"

void SPI_Slave::init()
{
    spi_.init();
}

void SPI_Slave::sendData(uint8_t *data, uint32_t size, bool blockingMode)
{
    spi_.sendData(data, size);
}

void SPI_Slave::readData(uint8_t *data, uint32_t size)
{
    spi_.readData(data, size);
}
