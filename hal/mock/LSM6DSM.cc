#include "LSM6DSM.h"

extern bool isReadRequested;
extern int16_t data;
extern LSM6DSM::State *stateIMU;

LSM6DSM::LSM6DSM(board::spi_identifier spi_name) : SPI_Slave(spi_name)
{
    stateIMU = &state_;
    isReadRequested = false;
    state_ = INITIALIZING;
}

void LSM6DSM::configure()
{
}

void LSM6DSM::request_read()
{
    state_ = READY;
    isReadRequested = true;
}

void LSM6DSM::read()
{
    isReadRequested = false;

    imuData_[0] = data;
    imuData_[1] = data + 1;
    imuData_[2] = data + 2;

    imuData_[3] = data + 10;
    imuData_[4] = data + 11;
    imuData_[5] = data + 12;

    imuData_[6] = data + 20;

    buffer0_ = imuData_;
}

void LSM6DSM::checkConfiguration()
{
    state_ = INITIALIZED;
}

int16_t *LSM6DSM::getIMUData()
{
    return buffer0_;
}
