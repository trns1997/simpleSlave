#include "LSM6DSM.h"

extern bool isConfigured;
extern bool isReadRequested;
extern uint8_t data;

void LSM6DSM::configure()
{
    isConfigured = true;
    isReadRequested = false;
}

void LSM6DSM::request_read()
{
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

IMUData LSM6DSM::getIMUData()
{
    return buffer0_;
}
