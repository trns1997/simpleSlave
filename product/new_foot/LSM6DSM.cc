#include "LSM6DSM.h"

void LSM6DSM::configure()
{
    free_ = &buffer0_;
    consume_ = &buffer1_;
    std::vector<uint8_t> imuConfig{IMU_WRITE | ADDR_CTRL1_XL, ACC_GYRO_ODR_XL_1660Hz, ACC_GYRO_ODR_G_1660Hz, IF_INC | BDU, I2C_DISABLE};
    spi_.sendData(imuConfig, true);
}

void LSM6DSM::read()
{
    std::vector<uint8_t> txDataIMU(15, 0);
    txDataIMU[0] = IMU_READ | ADDR_TEMP;

    spi_.sendData(txDataIMU);
}

void LSM6DSM::bufferizeIMUData()
{
    IMUData imuData;
    std::vector<uint8_t> readDataIMU = getRawData();

    int16_t temperature_raw = ((int16_t)readDataIMU[2] << 8) + (int16_t)readDataIMU[1];

    imuData.gyroscope[0] = ((((int16_t)readDataIMU[4]) << 8) + (int16_t)readDataIMU[3]);
    imuData.gyroscope[1] = ((((int16_t)readDataIMU[6]) << 8) + (int16_t)readDataIMU[5]);
    imuData.gyroscope[2] = ((((int16_t)readDataIMU[8]) << 8) + (int16_t)readDataIMU[7]);

    imuData.accelerometer[0] = ((((int16_t)readDataIMU[10]) << 8) + (int16_t)readDataIMU[9]);
    imuData.accelerometer[1] = ((((int16_t)readDataIMU[12]) << 8) + (int16_t)readDataIMU[11]);
    imuData.accelerometer[2] = ((((int16_t)readDataIMU[14]) << 8) + (int16_t)readDataIMU[13]);

    imuData.temperatureSensor = (temperature_raw / 256) + 25;

    *free_ = imuData;
}

IMUData LSM6DSM::getIMUData()
{
    std::swap(free_, consume_);
    return *consume_;
}