#ifndef BMI088_H_
#define BMI088_H_

#include "GPIO.h"
#include "SPI_Slave.h"

// Details of register map: https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmi088-ds001.pdf 
// Register map of the IMU
#define ACC_CHIP_ID 0x00
#define GYRO_CHIP_ID 0x00
#define ACC_PWR_CONF 0x7C
#define ACC_PWR_CTRL 0x7D
#define ACC_CONF 0x40
#define ACC_RANGE 0x41

#define GYRO_RANGE 0x0F
#define GYRO_BANDWIDTH 0x10

#define ACC_SOFTRESET 0x7E
#define CMD 0x7E
#define INIT_DATA 0x5E
#define INTERNAL_STATUS 0x21

#define ACC_X_LSB 0x12
#define RATE_X_LSB 0x02
#define TEMP_MSB 0x22

#define GYRO_RAW_TO_RADS 0.00053263221
#define ACCEL_RAW_TO_MS2 0.00718681318

#define IMU_READ 0x80
#define IMU_WRITE 0x00

class BMI088 : public SPI_Slave
{
public:
    BMI088(board::spi_identifier spi_name);
    ~BMI088() = default;

    void configure() override;
    void request_read() override;
    void read() override;
    void checkConfiguration() override;

    int16_t *getIMUData();

private:
    int16_t *buffer0_;
    int16_t *buffer1_;
    int16_t **free_;
    int16_t **consume_;
    uint8_t step_ = 0;
    uint8_t readCycle_ = 0;
    bool continueRead_{true};
    uint8_t imuConfig_[3] = {};
    int16_t imuData_[8];
    GPIO gpio_cs_{board::SPI2_CH0_CS1};
};

#endif
