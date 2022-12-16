#include "Fibre.hpp"
#include "DataItem.hpp"

#include "LSM6DSM.h"

class IMUFibre : public Fibre
{
public:

    IMUFibre(): Fibre("IMUFibre")
    {
        FibreManager& thread = FibreManager::getInstance(THREAD_1MS_ID);
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
        static DataItem imuAccel0(IMU_ACCEL_0_ID, true);
        static DataItem imuAccel1(IMU_ACCEL_1_ID, true);
        static DataItem imuAccel2(IMU_ACCEL_2_ID, true);
        static DataItem imuGyro0(IMU_GYRO_0_ID, true);
        static DataItem imuGyro1(IMU_GYRO_1_ID, true);
        static DataItem imuGyro2(IMU_GYRO_2_ID, true);
        static DataItem imuTemp(IMU_TEMP_ID, true);

        boardIMU_.read();
        IMUData imuData = boardIMU_.getIMUData();

        imuAccel0.set(imuData.accelerometer[0]);
        imuAccel1.set(imuData.accelerometer[1]);
        imuAccel2.set(imuData.accelerometer[2]);
        imuGyro0.set(imuData.gyroscope[0]);
        imuGyro1.set(imuData.gyroscope[1]);
        imuGyro2.set(imuData.gyroscope[2]);
        imuTemp.set(imuData.temperatureSensor);

    }

private:
    LSM6DSM boardIMU_ {board::SPI1_CH0};
};

static IMUFibre imuFibre;

extern "C" void SPI_IMU_TX_Interrupt(void) {}
extern "C" void SPI_IMU_RX_Interrupt(void)
{
    imuFibre.Interrupt();
}

