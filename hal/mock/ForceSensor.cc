#include "ForceSensor.h"

extern bool isConfigured;
extern bool isReadRequested;
extern uint8_t data;

ForceSensor::ForceSensor(board::spi_identifier spi_name): SPI_Slave(spi_name)
{
    isConfigured = false;
    isReadRequested = false;
}

void ForceSensor::configure()
{
    isConfigured = true;
    isReadRequested = false;
}

void ForceSensor::request_read()
{
    isReadRequested = true;
}

void ForceSensor::read()
{
    isReadRequested = false;

    fsData_.f0 = data;
    fsData_.f1 = data+1;
    fsData_.f2 = data+2;
    fsData_.f3 = data+3;
    fsData_.f4 = data+4;
}

ForceSensorData ForceSensor::getForceSensorData()
{
    return fsData_;
}
