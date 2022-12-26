#include "LSM6DSM.h"


LSM6DSM::LSM6DSM(board::spi_identifier spi_name): SPI_Slave(spi_name)
{}

void LSM6DSM::configure()
{
    free_ = &buffer0_;
    consume_ = &buffer1_;

    uint8_t imuConfig[] = {IMU_WRITE | ADDR_CTRL1_XL, ACC_GYRO_ODR_XL_1660Hz, ACC_GYRO_ODR_G_1660Hz, IF_INC | BDU, I2C_DISABLE};
    uint32_t size = sizeof(imuConfig) / sizeof(imuConfig[0]);
    sendData(imuConfig, size);

    state_ = INITIALIZED;
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

IMUData LSM6DSM::getIMUData()
{
    std::swap(free_, consume_);
    return *consume_;
}
