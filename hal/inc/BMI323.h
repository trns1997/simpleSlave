#ifndef BMI323_H_
#define BMI323_H_

#include "SPI_Slave.h"

// Details of register map: 
// Register map of the IMU
#define CHIP_ID 0x00

#define ACC_CONF 0x20
#define GYRO_CONF 0x21

#define ACC_DATA_X 0x03

#define IMU_READ 0x80
#define IMU_WRITE 0x00

class BMI323 : public SPI_Slave
{
public:
    BMI323(board::spi_identifier spi_name);
    ~BMI323() = default;

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
    uint8_t imuConfig_[6] = {};
    int16_t imuData_[7];
};

#endif
