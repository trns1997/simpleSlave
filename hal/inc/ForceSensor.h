#ifndef ForceSensor_H_
#define ForceSensor_H_

#include "SPI_Slave.h"

struct ForceSensorData
{
    uint16_t f0;
    uint16_t f1;
    uint16_t f2;
    uint16_t f3;
    uint16_t f4;
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

private:
    uint16_t forceSensorCnt_    {0};
    ForceSensorData fsData_     {0};
    ForceSensorData buffer0_    {0};
    ForceSensorData buffer1_    {0};
    ForceSensorData *free_      {0};
    ForceSensorData *consume_   {0};
    bool continueRead_{true};
};

#endif
