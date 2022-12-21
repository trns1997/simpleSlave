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

    channelData_.channel0 = data;
    channelData_.channel1 = data+1;
    channelData_.channel2 = data+2;
    channelData_.channel3 = data+3;
    channelData_.channel4 = data+4;
}

ForceSensorData ForceSensor::getForceSensorData()
{
    return channelData_;
}
