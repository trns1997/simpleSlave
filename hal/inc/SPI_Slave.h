#ifndef SPI_Slave_H_
#define SPI_Slave_H_

#include <memory>

#include "spi_mapping.h"
#include "SPI.h"

class SPI_Slave
{
public:
    enum State
    {
        INITIALIZING,
        INITIALIZED,
        READY,
        ERROR
    };

    SPI_Slave(board::spi_identifier spi_name) : spi_(SPI(spi_name))
    {
    }
    virtual ~SPI_Slave() = default;

    void init();

    virtual void configure() = 0;
    virtual void request_read() = 0;
    virtual void read() = 0;
    virtual void checkConfiguration() = 0;

    void sendData(uint8_t *data, uint32_t size);
    State getState() { return state_; }

    void setState(State state) { state_ = state; }

    bool isBusy() { return IRQ_pending_; }
    void setBusy() { IRQ_pending_ = true; }
    void setAvailable() { IRQ_pending_ = false; }

protected:
    SPI spi_;
    State state_{INITIALIZING};
    void readData(uint8_t *data, uint32_t size);

    bool IRQ_pending_{false};
};

#endif
