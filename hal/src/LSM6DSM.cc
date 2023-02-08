#include "LSM6DSM.h"

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

    IMUData imuData;
    imuData.gyroscope[0] = ((((int16_t)data[4]) << 8) + (int16_t)data[3]);
    imuData.gyroscope[1] = ((((int16_t)data[6]) << 8) + (int16_t)data[5]);
    imuData.gyroscope[2] = ((((int16_t)data[8]) << 8) + (int16_t)data[7]);

    imuData.accelerometer[0] = ((((int16_t)data[10]) << 8) + (int16_t)data[9]);
    imuData.accelerometer[1] = ((((int16_t)data[12]) << 8) + (int16_t)data[11]);
    imuData.accelerometer[2] = ((((int16_t)data[14]) << 8) + (int16_t)data[13]);

    imuData.temperatureSensor = (temperature_raw / 256) + 25;

    *free_ = imuData;
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

IMUData LSM6DSM::getIMUData()
{
    std::swap(free_, consume_);
    return *consume_;
}
