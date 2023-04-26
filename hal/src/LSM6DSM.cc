#include "LSM6DSM.h"
#include <cstring>

LSM6DSM::LSM6DSM(board::spi_identifier spi_name) : SPI_Slave(spi_name)
{
}

void LSM6DSM::configure()
{
    free_ = &buffer0_;
    consume_ = &buffer1_;

    uint8_t size = 5;

    switch (step_)
    {
    case 0:
    {
        imuConfig_[0] = IMU_WRITE | ADDR_CTRL1_XL;
        imuConfig_[1] = ACC_GYRO_ODR_1660Hz | ACC_16G;
        imuConfig_[2] = ACC_GYRO_ODR_1660Hz;
        imuConfig_[3] = IF_INC | BDU;
        imuConfig_[4] = I2C_DISABLE;
        sendData(imuConfig_, size);
        break;
    }
    case 1:
    {
        imuConfig_[0] = {IMU_READ | ADDR_CTRL1_XL};
        sendData(imuConfig_, size);
        break;
    }
    }
}

void LSM6DSM::request_read()
{
    uint32_t size = 15;
    uint8_t txDataIMU[size] = {};
    txDataIMU[0] = IMU_READ | ADDR_TEMP;
    sendData(txDataIMU, size);
}

void LSM6DSM::read()
{
    uint32_t size = 15;
    uint8_t data[size] = {};
    readData(data, size);

    int16_t temperature_raw = ((int16_t)data[2] << 8) + (int16_t)data[1];

    int16_t gyroscopeX = ((((int16_t)data[4]) << 8) + (int16_t)data[3]);
    imuData_[0] = gyroscopeX;

    int16_t gyroscopeY = ((((int16_t)data[6]) << 8) + (int16_t)data[5]);
    imuData_[1] = gyroscopeY;

    int16_t gyroscopeZ = ((((int16_t)data[8]) << 8) + (int16_t)data[7]);
    imuData_[2] = gyroscopeZ;

    int16_t accelerometerX = ((((int16_t)data[10]) << 8) + (int16_t)data[9]);
    imuData_[3] = accelerometerX;

    int16_t accelerometerY = ((((int16_t)data[12]) << 8) + (int16_t)data[11]);
    imuData_[4] = accelerometerY;

    int16_t accelerometerZ = ((((int16_t)data[14]) << 8) + (int16_t)data[13]);
    imuData_[5] = accelerometerZ;

    int16_t temperatureSensor = (temperature_raw / 256) + 25;
    imuData_[6] = temperatureSensor;

    *free_ = imuData_;
}

void LSM6DSM::checkConfiguration()
{
    uint8_t rxData[5] = {};
    uint8_t size = 5;

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
        state_ = INITIALIZED;
        for (uint8_t i = 1; i < size; ++i)
        {
            if (rxData[i] != imuConfig_[i])
            {
                state_ = ERROR;
                break;
            }
        }
        break;
    }
    }
    step_++;
}

int16_t *LSM6DSM::getIMUData()
{
    std::swap(free_, consume_);
    return *consume_;
}
