#ifndef LSM6DSM_H_
#define LSM6DSM_H_

#include "SPI_Slave.h"

struct IMUData
{
    int16_t accelerometer[3];  /**< Raw data collected from the 3 axis of the accelerometer */
    int16_t gyroscope[3];      /**< Raw data collected from the 3 axis of the gyroscope */
    int16_t temperatureSensor; /**< Raw data collected from the temperature sensor */
};

enum IMUregisteraddresses
{
    ADDR_ACCEL_ANTI_ALIASING = 0x0U, /**< Anti aliasing register address [0-1] */
    ADDR_ACCEL_SCALE = 0x2U,         /**< Accelerometer scale register address [2-3] */
    ADDR_ACCEL_MODE = 0x4U,          /**< Accelerometer mode register address [4-7] */
    ADDR_GYRO_SCALE = 0x2U,          /**< Gyroscope scale register address [2-3] */
    ADDR_GYRO_MODE = 0x4U,           /**< Gyroscope mode register address [4-7] */
    ADDR_HPCF_G = 0x5U,              /**< HPCF G register address */
    ADDR_HP_G_EN = 0x7U,             /**< HP G register address */
    ADDR_CTRL1_XL = 0x10U,           /**< CTRL1_XL register address (accelerometer configuration) */
    ADDR_CTRL2_G = 0x11U,            /**< CTRL2_G register address (gyroscope configuration) */
    ADDR_CTRL3_C = 0x12U,            /**< CTRL3_C register address (general configuration) */
    ADDR_CTRL4_C = 0x13U,            /**< CTRL4_C register address (general configuration) */
    ADDR_CTRL5_C = 0x14U,            /**< CTRL5_C register address (general configuration) */
    ADDR_CTRL6_C = 0x15U,            /**< CTRL6_C register address (general configuration) */
    ADDR_CTRL7_G = 0x16U,            /**< CTRL7_C register address (gyroscope configuration) */
    ADDR_CTRL8_XL = 0x17U,           /**< CTRL8_XL register address (accelerometer configuration) */
    ADDR_TEMP = 0x20U,               /**< Temperature register address */
    ADDR_GYRO_X = 0x22U,             /**< Gyroscope first byte axis X register address */
    ADDR_GYRO_Y = 0x24U,             /**< Gyroscope first byte axis Y register address */
    ADDR_GYRO_Z = 0x26U,             /**< Gyroscope first byte axis Z register address */
    ADDR_ACCEL_X = 0x28U,            /**< Accelerometer first byte axis X register address */
    ADDR_ACCEL_Y = 0x2AU,            /**< Accelerometer first byte axis Y register address */
    ADDR_ACCEL_Z = 0x2CU,            /**< Accelerometer first byte axis Z register address */
    ADDR_ORIENT = 0x0U,              /**< Orientation register address [0-2] */
    ADDR_REG_IF_INC = 0x2U,          /**< I2C slave address register address */
    ADDR_REG_I2C_DISABLE = 0x2U      /**< I2C disable mode register address */
};

constexpr uint8_t IMU_READ = 0x80;
constexpr uint8_t IMU_WRITE = 0x00;
constexpr uint8_t ACC_GYRO_ODR_1660Hz = 0x80;
constexpr uint8_t ACC_16G = 0x04;
constexpr uint8_t IF_INC = 0x04; /**< Automatic address increment in multiple bytes read (logic or) */
constexpr uint8_t BDU = 0x40;    /**< Block data update mechanism(logic or) */
constexpr uint8_t I2C_DISABLE = 0x04;

class LSM6DSM : public SPI_Slave
{
public:
    LSM6DSM(board::spi_identifier spi_name);
    ~LSM6DSM() = default;

    void configure() override;
    void request_read() override;
    void read() override;
    void checkConfiguration() override;

    IMUData getIMUData();

private:
    IMUData buffer0_{0};
    IMUData buffer1_{0};
    IMUData *free_{0};
    IMUData *consume_{0};
    uint8_t step_ = 0;
    uint8_t imuConfig_[5] = {};
};

#endif
