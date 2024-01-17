#include "BMI088.h"
#include <cstring>

BMI088::BMI088(board::spi_identifier spi_name) : SPI_Slave(spi_name)
{
    gpio_cs_.resetPin();
}

void BMI088::configure()
{
    free_ = &buffer0_;
    consume_ = &buffer1_;

    uint8_t size = 2;

    switch (step_)
    {
    case 0:
    {
        imuConfig_[0] = IMU_WRITE | GYRO_RANGE;
        imuConfig_[1] = 0x01; // 1000 dps
        gpio_cs_.setPin();
        sendData(imuConfig_, size);

        break;
    }
    case 1:
    {
        imuConfig_[0] = IMU_READ | GYRO_RANGE;
        gpio_cs_.setPin();
        sendData(imuConfig_, size);

        break;
    }
    case 2:
    {
        imuConfig_[0] = IMU_WRITE | GYRO_BANDWIDTH;
        imuConfig_[1] = 0x82; // 1000 Hz
        gpio_cs_.setPin();
        sendData(imuConfig_, size);

        break;
    }
    case 3:
    {
        imuConfig_[0] = IMU_READ | GYRO_BANDWIDTH;
        gpio_cs_.setPin();
        sendData(imuConfig_, size);

        break;
    }
    case 4:
    {
        imuConfig_[0] = IMU_WRITE | ACC_PWR_CONF;
        imuConfig_[1] = 0x00; // Accel in active mode
        gpio_cs_.resetPin();
        sendData(imuConfig_, size);

        break;
    }
    case 5:
    {
        imuConfig_[0] = IMU_WRITE | ACC_CONF;
        imuConfig_[1] = 0xAC; // BWP: Normal, ODR: 1600 Hz
        gpio_cs_.resetPin();
        sendData(imuConfig_, size);

        break;
    }
    case 6:
    {
        size = 3;
        imuConfig_[0] = IMU_READ | ACC_CONF;
        gpio_cs_.resetPin();
        sendData(imuConfig_, size);

        break;
    }
    case 7:
    {
        imuConfig_[0] = IMU_WRITE | ACC_RANGE;
        imuConfig_[1] = 0x02; // 12g
        gpio_cs_.resetPin();
        sendData(imuConfig_, size);

        break;
    }
    case 8:
    {
        size = 3;
        imuConfig_[0] = IMU_READ | ACC_RANGE;
        gpio_cs_.resetPin();
        sendData(imuConfig_, size);

        break;
    }
    case 9:
    {
        imuConfig_[0] = IMU_WRITE | ACC_PWR_CTRL;
        imuConfig_[1] = 0x04; // Accel ON
        gpio_cs_.resetPin();
        sendData(imuConfig_, size);

        break;
    }
    }
}

void BMI088::checkConfiguration()
{
    uint8_t size = 3;
    uint8_t rxData[size] = {};

    readData(rxData, size);

    switch (step_)
    {
    case 0:
    {
        gpio_cs_.resetPin();

        break;
    }
    case 1:
    {
        gpio_cs_.resetPin();
        if (rxData[1] != imuConfig_[1])
        {
            state_ = ERROR;
            break;
        }

        break;
    }
    case 2:
    {
        gpio_cs_.resetPin();

        break;
    }
    case 3:
    {
        gpio_cs_.resetPin();
        if (rxData[1] != imuConfig_[1])
        {
            state_ = ERROR;
            break;
        }
        gpio_cs_.setPin();

        break;
    }
    case 4:
    {
        gpio_cs_.setPin();

        break;
    }
    case 5:
    {
        gpio_cs_.setPin();

        break;
    }
    case 6:
    {
        gpio_cs_.setPin();
        if (rxData[2] != imuConfig_[1])
        {
            state_ = ERROR;
            break;
        }

        break;
    }
    case 7:
    {
        gpio_cs_.setPin();

        break;
    }
    case 8:
    {
        gpio_cs_.setPin();
        if (rxData[2] != imuConfig_[1])
        {
            state_ = ERROR;
            break;
        }

        break;
    }
    case 9:
    {
        gpio_cs_.setPin();
        state_ = INITIALIZED;

        break;
    }
    }

    step_++;
}

void BMI088::request_read()
{
    uint32_t size = 8;
    uint8_t txDataIMU[size] = {};

    switch (readCycle_)
    {
    case 0:
    {
        txDataIMU[0] = IMU_READ | RATE_X_LSB;
        gpio_cs_.setPin();
        sendData(txDataIMU, size);

        break;
    }

    case 1:
    {
        txDataIMU[0] = IMU_READ | ACC_X_LSB;
        gpio_cs_.resetPin();
        sendData(txDataIMU, size);

        break;
    }
    case 2:
    {
        txDataIMU[0] = IMU_READ | TEMP_MSB;
        gpio_cs_.resetPin();
        sendData(txDataIMU, size);

        break;
    }
    }
}

void BMI088::read()
{
    uint32_t size = 8;
    uint8_t data[size] = {};

    readData(data, size);

    switch (readCycle_)
    {
    case 0:
    {
        gpio_cs_.resetPin();
        int16_t gyroscopeX = (int16_t)((data[2] << 8) + data[1]);
        imuData_[0] = gyroscopeX;

        int16_t gyroscopeY = (int16_t)((data[4] << 8) + data[3]);
        imuData_[1] = gyroscopeY;

        int16_t gyroscopeZ = (int16_t)((data[6] << 8) + data[5]);
        imuData_[2] = gyroscopeZ;

        readCycle_ = 1;
        gpio_cs_.setPin();

        break;
    }

    case 1:
    {
        gpio_cs_.setPin();
        int16_t accelerometerX = (int16_t)((data[3] << 8) + data[2]);
        imuData_[3] = accelerometerX;

        int16_t accelerometerY = (int16_t)((data[5] << 8) + data[4]);
        imuData_[4] = accelerometerY;

        int16_t accelerometerZ = (int16_t)((data[7] << 8) + data[6]);
        imuData_[5] = accelerometerZ;

        readCycle_ = 2;
        gpio_cs_.resetPin();

        break;
    }
    case 2:
    {
        gpio_cs_.setPin();
        int16_t temp_raw = (int16_t)((data[2] << 8) + data[3]);
        imuData_[6] = temp_raw;

        readCycle_ = 0;
        gpio_cs_.resetPin();
        continueRead_ = false;

        break;
    }

    default:
        break;
    }

    *free_ = imuData_;

    if (continueRead_)
    {
        request_read();
    }
}

int16_t *BMI088::getData()
{
    continueRead_ = true;
    std::swap(free_, consume_);
    return *consume_;
}
