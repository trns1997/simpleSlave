#include "ForceSensor.h"

extern bool isReadRequested;
extern uint8_t data;
extern ForceSensor::State *stateFS;

ForceSensor::ForceSensor(board::spi_identifier spi_name) : SPI_Slave(spi_name)
{
    stateFS = &state_;
    isReadRequested = false;
    state_ = INITIALIZING;
    continueRead_ = false;
}

void ForceSensor::configure()
{
    state_ = INITIALIZED;
}

void ForceSensor::request_read()
{
    state_ = READY;
    isReadRequested = true;
}

void ForceSensor::read()
{
    isReadRequested = false;

    channelData_.channel0 = data;
    channelData_.channel1 = data + 1;
    channelData_.channel2 = data + 2;
    channelData_.channel3 = data + 3;
    channelData_.channel4 = data + 4;
}

void ForceSensor::checkConfiguration()
{
}

ForceSensorData ForceSensor::getForceSensorData()
{
    return channelData_;
}
