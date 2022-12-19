#ifndef SPI_Slave_H_
#define SPI_Slave_H_

#include <memory>

#include "spi_mapping.h"
#include "SPI.h"

class SPI_Slave
{
public:
    SPI_Slave(board::spi_identifier spi_name) : spi_(SPI(spi_name))
    {
    }
    virtual ~SPI_Slave() = default;

    void init();
    virtual void configure() = 0;
    virtual void request_read() = 0;
    virtual void read() = 0;
    void sendData(uint8_t *data, uint32_t size, bool blockingMode = false);

protected:
    SPI spi_;
    void readData(uint8_t *data, uint32_t size);
};

#endif
