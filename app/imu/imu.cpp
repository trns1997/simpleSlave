#include "Fibre.hpp"
#include "DataModel.hpp"

#include "LSM6DSM.h"

class IMUFibre : public Fibre
{
public:

    IMUFibre(): Fibre("IMUFibre")
    {
        FibreManager& thread = FibreManager::getInstance(THREAD_1MS_ID);
        thread.Add(std::shared_ptr<Fibre>(std::shared_ptr<Fibre>{}, this));
    }

    ~IMUFibre() override {}

    void Init() override
    {
        boardIMU_.init();
    }

    void Run() override
    {
        if ( boardIMU_.isBusy() )
            return;

        if (boardIMU_.getState() == SPI_Slave::INITIALIZING)
        {
            boardIMU_.configure();
        }
        else
        {
            boardIMU_.request_read();
        }
        boardIMU_.setBusy();
    }

    void Interrupt()
    {

        static DataItem imuAccelX(DataItemId::IMU_ACCEL_X_ID, true);
        static DataItem imuAccelY(DataItemId::IMU_ACCEL_Y_ID, true);
        static DataItem imuAccelZ(DataItemId::IMU_ACCEL_Z_ID, true);
        static DataItem imuGyroX(DataItemId::IMU_GYRO_X_ID, true);
        static DataItem imuGyroY(DataItemId::IMU_GYRO_Y_ID, true);
        static DataItem imuGyroZ(DataItemId::IMU_GYRO_Z_ID, true);
        static DataItem imuTemp(DataItemId::IMU_TEMP_ID, true);

        if (boardIMU_.getState() == SPI_Slave::INITIALIZED)
        {
            boardIMU_.setState(SPI_Slave::READY);
        }
        else if (boardIMU_.getState() == SPI_Slave::READY)
        {
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
        boardIMU_.setAvailable();
    }

private:
    LSM6DSM boardIMU_ {board::SPI2_CH0};
};

static IMUFibre imuFibre;

extern "C" void SPI_IMU_TX_Interrupt(void) {}
extern "C" void SPI_IMU_RX_Interrupt(void)
{
    imuFibre.Interrupt();
}

