#ifndef ForceSensor_H_
#define ForceSensor_H_

#include "SPI_Slave.h"

class ForceSensor : public SPI_Slave
{
public:
    ForceSensor(board::spi_identifier spi_name);
    ~ForceSensor() = default;

    void configure() override;
    void request_read() override;
    void read() override;
    void checkConfiguration() override;

    int16_t *getData();

    bool isReadingFinished() { return !continueRead_; };

private:
    uint16_t channelCnt_;
    int16_t channelData_[5];
    bool continueRead_{true};
    uint8_t config_[3] = {};
};

#endif
