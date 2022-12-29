#ifndef ForceSensor_H_
#define ForceSensor_H_

#include "SPI_Slave.h"

struct ForceSensorData
{
    uint16_t channel0;
    uint16_t channel1;
    uint16_t channel2;
    uint16_t channel3;
    uint16_t channel4;
};

class ForceSensor : public SPI_Slave
{
public:
    ForceSensor(board::spi_identifier spi_name);
    ~ForceSensor() = default;

    void configure() override;
    void request_read() override;
    void read() override;

    ForceSensorData getForceSensorData();

    bool isReadingFinished () { return !continueRead_; } ;

private:
    uint16_t channelCnt_    {0};
    ForceSensorData channelData_     {0};
    ForceSensorData buffer0_    {0};
    ForceSensorData buffer1_    {0};
    ForceSensorData *free_      {0};
    ForceSensorData *consume_   {0};
    bool continueRead_{true};
};

#endif
