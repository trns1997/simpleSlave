#include "BMI270.h"
#include <cstring>

BMI270::BMI270(board::spi_identifier spi_name) : SPI_Slave(spi_name)
{
}

void BMI270::configure()
{
    free_ = &buffer0_;
    consume_ = &buffer1_;

    uint8_t size = 3;

    switch (step_)
    {
    case 0:
    {
        // Dummy Read operation to set chip to SPI mode
        imuConfig_[0] = IMU_READ | CHIP_ID;
        sendData(imuConfig_, size);
        break;
    }
    case 1:
    {
        // Dummy Read operation to set chip to SPI mode
        imuConfig_[0] = IMU_READ | CHIP_ID;
        sendData(imuConfig_, size);
        break;
    }
    }
}

void BMI270::request_read()
{
    uint32_t size = 16;
    uint8_t txDataIMU[size] = {};
    txDataIMU[0] = IMU_READ | REG_ACCEL_XOUT_H;
    sendData(txDataIMU, size);
}

void BMI270::read()
{
    uint32_t size = 16;
    uint8_t data[size] = {};
    readData(data, size);

    int16_t gyroscopeX = ((((int16_t)data[9]) << 8) + (int16_t)data[8]);
    imuData_[0] = gyroscopeX;

    int16_t gyroscopeY = ((((int16_t)data[11]) << 8) + (int16_t)data[10]);
    imuData_[1] = gyroscopeY;

    int16_t gyroscopeZ = ((((int16_t)data[13]) << 8) + (int16_t)data[12]);
    imuData_[2] = gyroscopeZ;

    int16_t accelerometerX = ((((int16_t)data[3]) << 8) + (int16_t)data[2]);
    imuData_[3] = accelerometerX;

    int16_t accelerometerY = ((((int16_t)data[5]) << 8) + (int16_t)data[4]);
    imuData_[4] = accelerometerY;

    int16_t accelerometerZ = ((((int16_t)data[7]) << 8) + (int16_t)data[6]);
    imuData_[5] = accelerometerZ;

    int16_t temperature_raw = ((int16_t)data[15] << 8) + (int16_t)data[14];
    imuData_[6] = temperature_raw;

    *free_ = imuData_;
}

void BMI270::checkConfiguration()
{
    uint8_t size = 3;
    uint8_t rxData[size] = {};

    switch (step_)
    {
    case 0:
    {
        readData(rxData, size);
        break;
    }
    case 1:
    {
        readData(rxData, size);
        break;
    }
    }
    step_++;
}

int16_t *BMI270::getData()
{
    std::swap(free_, consume_);
    return *consume_;
}
