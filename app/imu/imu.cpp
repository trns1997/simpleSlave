#include "Fibre.hpp"
#include "DataItem.hpp"

#include "LSM6DSM.h"

class IMUFibre : public Fibre
{
public:
    IMUFibre() : Fibre("IMUFibre")
    {
        FibreManager &thread = FibreManager::getInstance(THREAD_1MS_ID);
        thread.Add(std::shared_ptr<Fibre>(this));
    }

    virtual void Init()
    {
        boardIMU_.init();
        boardIMU_.configure();
    }

    virtual void Run()
    {
        boardIMU_.request_read();
    }

    void Interrupt()
    {
        static DataItem<int16_t> imuAccelX(IMU_ACCEL_X_ID, true);
        static DataItem<int16_t> imuAccelY(IMU_ACCEL_Y_ID, true);
        static DataItem<int16_t> imuAccelZ(IMU_ACCEL_Z_ID, true);
        static DataItem<int16_t> imuGyroX(IMU_GYRO_X_ID, true);
        static DataItem<int16_t> imuGyroY(IMU_GYRO_Y_ID, true);
        static DataItem<int16_t> imuGyroZ(IMU_GYRO_Z_ID, true);
        static DataItem<int16_t> imuTemp(IMU_TEMP_ID, true);

        boardIMU_.read();
        IMUData imuData = boardIMU_.getIMUData();

        imuAccelX.set(imuData.accelerometer[0]);
        imuAccelY.set(imuData.accelerometer[1]);
        imuAccelZ.set(imuData.accelerometer[2]);
        imuGyroX.set(imuData.gyroscope[0]);
        imuGyroY.set(imuData.gyroscope[1]);
        imuGyroZ.set(imuData.gyroscope[2]);
        imuTemp.set(imuData.temperatureSensor);
    }

private:
    LSM6DSM boardIMU_{board::SPI1_CH0};
};

static IMUFibre imuFibre;

extern "C" void SPI_IMU_TX_Interrupt(void) {}
extern "C" void SPI_IMU_RX_Interrupt(void)
{
    imuFibre.Interrupt();
}
