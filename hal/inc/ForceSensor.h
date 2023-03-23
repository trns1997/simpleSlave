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

    uint16_t *getForceSensorData();

    bool isReadingFinished() { return !continueRead_; };

private:
    uint16_t channelCnt_;
    uint16_t channelData_[5];
    uint16_t *buffer0_;
    uint16_t *buffer1_;
    uint16_t **free_;
    uint16_t **consume_;
    bool continueRead_{true};
    uint8_t config_[3] = {};
};

#endif
