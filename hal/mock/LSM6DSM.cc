#include "LSM6DSM.h"

extern bool isReadRequested;
extern uint8_t data;
extern LSM6DSM::State * stateIMU;

LSM6DSM::LSM6DSM(board::spi_identifier spi_name): SPI_Slave(spi_name)
{
    stateIMU = &state_;
    isReadRequested = false;
    state_ = INITIALIZING;
}

void LSM6DSM::configure()
{
    state_ = INITIALIZED;
}

void LSM6DSM::request_read()
{
    state_ = READY;
    isReadRequested = true;
}

void LSM6DSM::read()
{
    isReadRequested = false;

    buffer0_.accelerometer[0] = data;
    buffer0_.accelerometer[1] = data+1;
    buffer0_.accelerometer[2] = data+2;

    buffer0_.gyroscope[0] = data+10;
    buffer0_.gyroscope[1] = data+11;
    buffer0_.gyroscope[2] = data+12;

    buffer0_.temperatureSensor = data+20;
}

void LSM6DSM::checkConfiguration()
{
}

IMUData LSM6DSM::getIMUData()
{
    return buffer0_;
}
