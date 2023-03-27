#include "LSM6DSM.h"

extern bool isReadRequested;
extern uint8_t data;
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

    buffer0_[0] = data;
    buffer0_[1] = data + 1;
    buffer0_[2] = data + 2;

    buffer0_[3] = data + 10;
    buffer0_[4] = data + 11;
    buffer0_[5] = data + 12;

    buffer0_[6] = data + 20;
}

void LSM6DSM::checkConfiguration()
{
    state_ = INITIALIZED;
}

int16_t *LSM6DSM::getIMUData()
{
    return buffer0_;
}
