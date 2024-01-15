#include "BMI323.h"
#include <cstring>

BMI323::BMI323(board::spi_identifier spi_name) : SPI_Slave(spi_name)
{
}

void BMI323::configure()
{
    free_ = &buffer0_;
    consume_ = &buffer1_;

    uint8_t size = 6;

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
    case 2:
    {
        imuConfig_[0] = IMU_WRITE | ACC_CONF;
        imuConfig_[1] = 0x3C;
        imuConfig_[2] = 0x70;
        imuConfig_[3] = 0x3C;
        imuConfig_[4] = 0x70;
        sendData(imuConfig_, size);
        break;
    }
    case 3:
    {
        imuConfig_[0] = IMU_READ | ACC_CONF;
        sendData(imuConfig_, size);
        break;
    }
    }
}

void BMI323::request_read()
{
    uint32_t size = 16;
    uint8_t txDataIMU[size] = {};
    txDataIMU[0] = IMU_READ | ACC_DATA_X;
    sendData(txDataIMU, size);
}

void BMI323::read()
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

void BMI323::checkConfiguration()
{
    uint8_t rxData[6] = {};
    uint8_t size = 6;

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
    case 2:
    {
        readData(rxData, size);
        break;
    }
    case 3:
    {
        readData(rxData, size);
        state_ = INITIALIZED;
        for (uint8_t i = 2; i < size; ++i)
        {
            if (rxData[i] != imuConfig_[i-1])
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

int16_t *BMI323::getIMUData()
{
    std::swap(free_, consume_);
    return *consume_;
}
